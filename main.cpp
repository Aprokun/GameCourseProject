#include <SFML/Graphics.hpp>
#include "Hero.h"

using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode(640, 480), "SFML APP");

    Hero hero(10.0f, 10.0f, 24, 25, 2.0, "tiles/characters.png");

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            hero.setMoveSpeed(0.1);
            hero.setCurrentMoveFrame(hero.getCurrentMoveFrame() + 0.005f * time);
            hero.setCurDir(Hero::RIGHT);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            hero.setMoveSpeed(0.1);
            hero.setCurrentMoveFrame(hero.getCurrentMoveFrame() + 0.005f * time);
            hero.setCurDir(Hero::DOWN);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            hero.setMoveSpeed(0.1);
            hero.setCurrentMoveFrame(hero.getCurrentMoveFrame() + 0.005f * time);
            hero.setCurDir(Hero::LEFT);
        }

        hero.update(time);

        window.clear();
        window.setView(hero.getCamera().getView());
        window.draw(hero.getSprite());
        window.display();
    }
}