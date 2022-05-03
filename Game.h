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
public:

    static void start();

    static void setPressedKeyset(HeroEntity *hero);

    static void handleEntityInteraction(
            RenderWindow &window, HeroEntity *hero, vector<Entity *> &entities, float time,
            const Object &endBlock);

    static void
    initEnemies(AnimationManager &bigBamboniAM, AnimationManager &smallBamboniAM, Level &level, EntityFactory &factory,
                vector<Entity *> &entities);

    static void updateTime(Clock &clock, float &time);
};


#endif //SFMLTRAIN_GAME_H
