//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(500, 500), "SFML APP");

    if (!isMenu) {
        drawMenu(window);
    }

    Image img;
    img.loadFromFile("EntitiesTexture/characters.png");
    Texture texture;
    texture.loadFromImage(img);

    AnimationManager qManager;
    qManager.create("stay", texture, 0, 0, 23, 24, 1, 0.002, 23, false, false);
    qManager.create("walk", texture, 0, 0, 23, 24, 2, 0.006, 23, false, true);

    Level level;
    level.loadFromXmlFile("Levels/level1/level.tmx");

    EntityFactory factory(level);
    Entity *hero = factory.getEntity(EntityFactory::HERO, qManager, 5, 5);

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 650;

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) hero->setKeyValue("A", true);
        if (Keyboard::isKeyPressed(Keyboard::Right)) hero->setKeyValue("D", true);
        if (Keyboard::isKeyPressed(Keyboard::Up)) hero->setKeyValue("W", true);
        if (Keyboard::isKeyPressed(Keyboard::Down)) hero->setKeyValue("S", true);

        hero->update(time);
        hero->draw(window);
        window.display();
    }
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