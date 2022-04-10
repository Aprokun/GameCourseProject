//
// Created by lagri on 03.04.2022.
//

#include "HeroEntity.h"

void HeroEntity::update(float time) {
    currentMoveDir = keyCheck();


}

Dir HeroEntity::keyCheck() {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        return LEFT;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        return UP;
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        return RIGHT;
    } else if (Keyboard::isKeyPressed(Keyboard::S)) {
        return DOWN;
    }
}

HeroEntity::HeroEntity(AnimationManager &a, Level &level, int x, int y) : Entity(a, x, y) {
    option("Hero", 0, 5, "stay");
    currentState = STAY;
    isHit = false;
    objects = level.getAllObjects();
}
