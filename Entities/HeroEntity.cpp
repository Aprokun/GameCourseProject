//
// Created by lagri on 03.04.2022.
//

#include "HeroEntity.h"

void HeroEntity::update(float time) {
    keyCheck();

    //TODO: переделать строковые значения анимаций
    // на константные (напр. enum)
    if (currentState == STAY) {
        animationManager.setCurrentAnimation("stay");
    } else if (currentState == WALK) {
        animationManager.setCurrentAnimation("walk");
    } else if (currentState == JUMP) {
        animationManager.setCurrentAnimation("jump");
    }

    if (isFlip) animationManager.flip(true);

    x += dx * time;

    dy += 0.0005f * time;
    y += dy * time;

    animationManager.update(time);

    keys["W"] = keys["A"] = keys["S"] = keys["D"] = false;

}

void HeroEntity::keyCheck() {
    if (keys["A"]) {
        currentMoveDir = LEFT;
        if (currentState == STAY) {
            dx = -0.1;
            isFlip = false;
            currentState = WALK;
        }
    } else if (keys["D"]) {
        currentMoveDir = RIGHT;
        if (currentState == STAY) {
            dx = 0.1;
            isFlip = true;
            currentState = WALK;
        }
    } else if (keys["W"]) {
        if (currentState == STAY || currentState == WALK) {
            isFlip = false;
            dy = -0.27;
        }
    }
}

HeroEntity::HeroEntity(AnimationManager &a, Level &level, int x, int y) : Entity(a, x, y) {
    option("Hero", 0, 5, "stay");
    currentState = STAY;
    isHit = false;
    objects = level.getAllObjects();
}
