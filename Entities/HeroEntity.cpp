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
    collision(0);

    dy += 0.0005f * time;
    y += dy * time;
    collision(1);

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

void HeroEntity::collision(int num) {
    for (auto &object: objects)
        if (getRect().intersects(object.rect)) {
            if (object.name == "solid") {
                if (dy > 0 && num == 1) {
                    y = object.rect.top - h;
                    dy = 0;
                    currentState = STAY;
                }
                if (dy < 0 && num == 1) {
                    y = object.rect.top + object.rect.height;
                    dy = 0;
                }
                if (dx > 0 && num == 0) { x = object.rect.left - w; }
                if (dx < 0 && num == 0) { x = object.rect.left + object.rect.width; }
            }

            if (object.name == "SlopeLeft") {
                FloatRect r = object.rect;
                int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
                if (y > y0)
                    if (x + w / 2 > r.left) {
                        y = y0;
                        dy = 0;
                        currentState = STAY;
                    }
            }

            if (object.name == "SlopeRight") {
                FloatRect r = object.rect;
                int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
                if (y > y0)
                    if (x + w / 2 < r.left + r.width) {
                        y = y0;
                        dy = 0;
                        currentState = STAY;
                    }
            }

        }
}

HeroEntity::HeroEntity(AnimationManager &a, Level &level, int x, int y) : Entity(a, x, y) {

    option("Hero", 0, 5, "stay");

    currentState = STAY;

    isHit = false;

    objects = level.getAllObjects();
}
