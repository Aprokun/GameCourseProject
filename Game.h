//
// Created by lagri on 14.04.2022.
//

#ifndef SFMLTRAIN_GAME_H
#define SFMLTRAIN_GAME_H

#include <SFML/Graphics.hpp>
#include "EntityFactory.h"
#include "SubjectFactory.h"

using namespace sf;
using namespace std;

class Game {
public:

    static void start();

    static void setPressedKeyset(HeroEntity *hero);

    static void handleEntities(RenderWindow &window, HeroEntity *hero, vector<Entity *> &entities, float time);

    static void
    initEnemies(vector<Entity *> &entities, AnimationManager &bigBamboniAM, AnimationManager &smallBamboniAM,
                Level &level, EntityFactory &factory);

    static void updateTime(Clock &clock, float &time);

    static void
    initSubjects(AnimationManager &coinAM, AnimationManager &padlockAM, AnimationManager &keyAM, Level &level,
                 SubjectFactory &subjectFactory, vector<Subject *> &subjects);

    static void handleSubjects(RenderWindow &window, HeroEntity *hero, vector<Subject *> &subjects, float time);


    static void drawAllInfoText(RenderWindow &window, const HeroEntity *hero);

    static void drawKeyAvailability(RenderWindow &window, const HeroEntity *hero);

    static void drawCoinsAvailability(RenderWindow &window, const HeroEntity *hero);
};


#endif //SFMLTRAIN_GAME_H
