#include <SFML/Graphics.hpp>
#include "EntityFactory.h"
#include <vector>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "SFML APP");

    vector<Entity> entities;

    Level l;
    EntityFactory factory(l);

    try {
        l.loadFromXmlFile("Levels/level2/level.tmx");
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        time /= 800;

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        l.draw(window);
        window.display();
    }
}