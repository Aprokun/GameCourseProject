//
// Created by lagri on 14.04.2022.
//

#include "Game.h"

void Game::start() {
    RenderWindow window(VideoMode(800, 600), "SFML APP");

    if (isMenu) {
        drawMenu(window);
    }

    Image img;
    img.loadFromFile("EntitiesTexture/characters.png");
    Texture q;
    q.loadFromImage(img);

    AnimationManager qManager;
    qManager.create("stay", q, 0, 0, 23, 24, 1, 0.002, 23, false, false);
    qManager.create("walk", q, 0, 0, 23, 24, 2, 0.006, 23, false, true);

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        time /= 500;

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        qManager.setCurrentAnimation("stay");

        if (Keyboard::isKeyPressed(Keyboard::D)) qManager.setCurrentAnimation("walk");

        qManager.update(time);

        window.clear(Color(255, 255, 255));
        qManager.draw(window, 50, 50);
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
                default: {
                    cerr << "Произошла ошибка при выборе пункта меню" << endl;
                    isMenu = false;
                }
            }
        }

        window.draw(selectLevelSprite);
        window.draw(quitGameSprite);

        window.display();
    }
}