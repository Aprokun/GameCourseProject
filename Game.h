//
// Created by lagri on 14.04.2022.
//

#ifndef SFMLTRAIN_GAME_H
#define SFMLTRAIN_GAME_H

#include <SFML/Graphics.hpp>
#include "EntityFactory.h"

using namespace sf;
using namespace std;

class Game {
private:
    bool isMenu;

    void drawMenu(RenderWindow &window);

public:
    Game();

    void setIsMenu(bool isMenu);

    void start();
};


#endif //SFMLTRAIN_GAME_H
