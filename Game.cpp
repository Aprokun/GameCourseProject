//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(450, 280), "SFML APP");
    View camera(FloatRect(0, 0, 450, 280));

    if (!isMenu) {
        drawMenu(window);
    }

    Image img;
    img.loadFromFile("EntitiesTexture/characters.png");

    Texture textureEnemy;
    textureEnemy.loadFromImage(img);

    Texture textureHero;
    textureHero.loadFromImage(img);

    Texture textureBigBamboni;
    textureBigBamboni.loadFromImage(img);

    AnimationManager heroAM;
    heroAM.loadFromXml("Animation/Hero/anims.xml", textureHero);

    AnimationManager bigBamboniAM;
    bigBamboniAM.loadFromXml("Animation/BigBamboni/anims.xml", textureBigBamboni);

    Level level;
    level.loadFromXmlFile("Levels/level1/level.tmx");

    Object heroObj = level.getObject("hero");

    vector<Entity *> entities;
    EntityFactory factory(level);

    Entity *hero = factory.getEntity(EntityFactory::HERO, heroAM, heroObj.rect.left, heroObj.rect.top - 20);

    for (const auto &enemy: level.getObjects("enemy")) {
        entities.push_back(factory.getEntity(EntityFactory::BIGBAMBONI, bigBamboniAM, enemy.rect.left, enemy.rect.top));
    }

    Clock clock;

    cout << "Game ran" << endl;
    while (window.isOpen()) {
        window.clear();

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 650;
        if (time > 40) time = 40;

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        level.draw(window);

        if (Keyboard::isKeyPressed(Keyboard::W)) hero->setKeyValue("W", true);
        if (Keyboard::isKeyPressed(Keyboard::A)) hero->setKeyValue("A", true);
        if (Keyboard::isKeyPressed(Keyboard::S)) hero->setKeyValue("S", true);
        if (Keyboard::isKeyPressed(Keyboard::D)) hero->setKeyValue("D", true);

        camera.setCenter(hero->getX(), hero->getY());

        for (auto &entity: entities) {
            entity->update(time);
            entity->draw(window);
        }

        hero->update(time);
        hero->draw(window);

        window.display();
    }

    cout << "Game stopped" << endl;

    exit(0);
}

Game::Game() {
    isMenu = true;
}

void Game::drawMenu(RenderWindow &window) {
    Texture selectLevelTexture, quitGameTexture;
    selectLevelTexture.loadFromFile("Menu/select_level.png");
    quitGameTexture.loadFromFile("Menu/quit_game.png");

    Sprite selectLevelSprite, quitGameSprite;
    selectLevelSprite.setTexture(selectLevelTexture);
    quitGameSprite.setTexture(quitGameTexture);

    selectLevelSprite.setPosition(400, 200);
    quitGameSprite.setPosition(400, 400);

    int menuNum;
    while (isMenu) {
        selectLevelSprite.setColor(Color::White);
        quitGameSprite.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        if (IntRect(400, 200, 50, 50).contains(Mouse::getPosition(window))) {
            selectLevelSprite.setColor(Color::Blue);
            menuNum = 1;
        } else if (IntRect(400, 400, 50, 50).contains(Mouse::getPosition(window))) {
            quitGameSprite.setColor(Color::Blue);
            menuNum = 2;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            switch (menuNum) {
                case 2: {
                    isMenu = false;
                    window.close();
                    break;
                }
                case 1: {
                    //TODO:сделать переход на следующее окно выбора лвла
                    break;
                }
            }
        }

        window.draw(selectLevelSprite);
        window.draw(quitGameSprite);

        window.display();
    }
}