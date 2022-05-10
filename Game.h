//
// Created by lagri on 14.04.2022.
//

#ifndef SFMLTRAIN_GAME_H
#define SFMLTRAIN_GAME_H

#include <SFML/Graphics.hpp>
#include "Factories/EntityFactory.h"
#include "Factories/SubjectFactory.h"
#include "Camera.h"

using namespace sf;
using namespace std;

class Game {
public:

    static const int RELOAD_STATUS = 100;

    static int start();

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


    static void drawAllInfoText(RenderWindow &window, Camera camera, const HeroEntity *hero);

    static void drawKeyAvailability(RenderWindow &window, Camera camera, const HeroEntity *hero);

    static void drawHeroDeadText(RenderWindow &window, Camera camera);

    static void drawCoinsAvailability(RenderWindow &window, Camera camera, const HeroEntity *hero);

    static void handleHero(RenderWindow &window, Camera camera, HeroEntity *hero, float time);

    static void reload();
};


#endif //SFMLTRAIN_GAME_H
