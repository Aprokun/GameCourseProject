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

enum State {
    STAY, WALK, JUMP, CLIMB
};

enum Dir {
    UP, RIGHT, DOWN, LEFT
};

class HeroEntity : public Entity {
private:
    bool isOnLadder, isHit;
    map<string, bool> key;
    Dir currentMoveDir;

    static Dir keyCheck();

public:
    void update(float time) override;
};


#endif //SFMLTRAIN_HEROENTITY_H
