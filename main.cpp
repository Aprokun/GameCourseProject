#include <SFML/Graphics.hpp>
#include "entities/HeroEntity.h"
#include "AnimationManager.h"

using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode(640, 480), "SFML APP");

    Texture t;
    t.loadFromFile("tiles/characters.png");

    AnimationManager animationManager;
    animationManager.create("walk", t, 0, 0, 24, 25, 2, 0.05);

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        time /= 800;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(sf::Keyboard::D) || Keyboard::isKeyPressed(Keyboard::A)) {
            animationManager.setCurrentAnimation("walk");
        }

        animationManager.update(time);
        animationManager.draw(window, 50, 100);

        window.display();
    }
}