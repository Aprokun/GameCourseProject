//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(900, 900), "SFML APP");

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

    auto *hero = new HeroEntity(heroAM, level, heroObj.rect.left, heroObj.rect.top);

    for (const auto &enemy: level.getObjects("enemy")) {
        entities.push_back(factory.getEntity(EntityFactory::BIGBAMBONI, bigBamboniAM, enemy.rect.left, enemy.rect.top));
    }

    const Object &endBlock = level.getObject("end");

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

        for (auto &entity: entities) {

            if (entity->getObjName() == "enemy") {

                if (entity->getHealth() <= 0) continue;

                if (hero->getRect().intersects(entity->getRect())) {

                    if (hero->getDy() > 0.0) {

                        entity->setDx(0.0);
                        hero->setDy(-0.2);

                        entity->setHealth(0);

                    } else if (!hero->isHit()) {

                        hero->setHealth(hero->getHealth() - 5);

                        hero->setIsHit(true);

                        if (hero->getCurrentMoveDir() == Dir::RIGHT) {
                            hero->setX(hero->getX() + 10);
                        } else {
                            hero->setX(hero->getX() - 10);
                        }
                    }
                }
            }

            entity->update(time);
            entity->draw(window);
        }


        if (hero->getRect().intersects(endBlock.rect)) {
            cout << "Level passed!!!" << "Congrats!" << endl;
            exit(0);
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