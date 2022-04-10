//
// Created by lagri on 03.04.2022.
//

#ifndef SFMLTRAIN_HEROENTITY_H
#define SFMLTRAIN_HEROENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "../Camera.h"

using namespace sf;
using namespace std;

enum Dir {
    UP, RIGHT, DOWN, LEFT
};

class HeroEntity : public Entity {
private:
    bool isOnLadder, isHit;
    map<string, bool> key;
    Dir currentMoveDir;

    enum State {
        STAY, WALK, JUMP, CLIMB
    } currentState;

    static Dir keyCheck();

public:
    HeroEntity(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;
};


#endif //SFMLTRAIN_HEROENTITY_H
