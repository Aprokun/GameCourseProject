//
// Created by lagri on 03.04.2022.
//

#include "HeroEntity.h"

void HeroEntity::update(float time) {

    if (hit) {
        timer -= time;
        if (timer <= 0) hit = false;
    }

    handleKey();

    handleAnimation(time);

    x += dx * time;
    collision(0);

    dy += 0.0005f * time;
    y += dy * time;
    collision(1);

    animationManager.update(time);
}

void HeroEntity::handleAnimation(float time) {

    if (currentState == STAY) {
        animationManager.setCurrentAnimation("stay");
    }

    if (currentState == WALK) {
        animationManager.setCurrentAnimation("walk");
    }

    if (currentState == JUMP) {
        animationManager.setCurrentAnimation("jump");
    }

    if (flip) {
        animationManager.flip(true);
    } else {
        animationManager.flip(false);
    }

    animationManager.update(time);
}

void HeroEntity::handleKey() {

    if (keys["A"]) {

        flip = false;
        dx = -0.1;

        if (currentState == STAY) {
            currentState = WALK;
        }

    } else if (keys["D"]) {

        flip = true;
        dx = 0.1;

        if (currentState == STAY) {
            currentState = WALK;
        }

    } else if (keys["W"]) {

        if (currentState == STAY || currentState == WALK) {
            currentState = JUMP;
            dy = -0.27;
        }

    } else if (!(keys["R"] && keys["L"])) {

        dx = 0;

        if (currentState == WALK) {
            currentState = STAY;
        }
    }

    keys["W"] = keys["A"] = keys["S"] = keys["D"] = false;
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

                if (dx > 0 && num == 0) {
                    x = object.rect.left - w;
                }

                if (dx < 0 && num == 0) {
                    x = object.rect.left + object.rect.width;
                }
            }

            if (object.name == "SlopeLeft") {

                FloatRect r = object.rect;

                int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;

                if (y > y0) {
                    if (x + w / 2 > r.left) {

                        y = y0;
                        dy = 0;
                        currentState = STAY;
                    }
                }
            }

            if (object.name == "SlopeRight") {

                FloatRect r = object.rect;

                int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;

                if (y > y0) {

                    if (x + w / 2 < r.left + r.width) {

                        y = y0;
                        dy = 0;
                        currentState = STAY;
                    }
                }
            }

        }
}

void HeroEntity::setKeyValue(const string &key, bool value) {
    keys[key] = value;
}

HeroEntity::HeroEntity(AnimationManager &a, Level &level, int x, int y) : Entity(a, x, y) {

    option("Hero", 0, 5, "stay");

    currentState = STAY;

    hasKey = hit = flip = false;

    coins = 0;

    objects = level.getAllObjects();
}

string HeroEntity::getObjName() {
    return "hero";
}

bool HeroEntity::isHit() const {
    return hit;
}

void HeroEntity::setIsHit(bool isHit) {
    hit = isHit;
}

bool HeroEntity::isHasKey() const {
    return hasKey;
}

void HeroEntity::setHasKey(bool hasKey) {
    HeroEntity::hasKey = hasKey;
}

unsigned int HeroEntity::getCoins() const {
    return coins;
}

void HeroEntity::setCoins(unsigned int coins) {
    this->coins = coins;
}

void HeroEntity::setTimer(int ms) {
    this->timer = ms;
}
