//
// Created by lagri on 09.04.2022.
//

#include "Entity.h"

#include <utility>

Entity::Entity(AnimationManager &a, int x, int y) {
    animationManager = a;
    this->x = x;
    this->y = y;
    dir = 0;

    isAlive = true;
    timer = 0;
    timerEnd = 0;
    dx = dy = 0;
}

void Entity::draw(RenderWindow &window) {
    animationManager.draw(window, x, y + h);
}

FloatRect Entity::getRect() {
    return FloatRect(x, y, w, h);
}

void Entity::option(string name, float speed, int health, string initAnimationName) {
    this->name = std::move(name);
    if (!initAnimationName.empty()) animationManager.setCurrentAnimation(initAnimationName);
    w = animationManager.getCurrenctAnimationWidth();
    h = animationManager.getCurrentAnimationHeight();
    dx = speed;
    this->health = health;
}

void Entity::setKeyValue(const string &key, bool value) {
    keys[key] = value;
}

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}
