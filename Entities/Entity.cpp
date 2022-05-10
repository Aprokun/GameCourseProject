//
// Created by lagri on 09.04.2022.
//

#include "Entity.h"

Entity::Entity(AnimationManager &a, int x, int y) {

    animationManager = a;

    this->x = x;
    this->y = y;

    alive = true;

    timer = 0;

    timerEnd = 0;

    dx = dy = 0;
}

void Entity::draw(RenderWindow &window) {
    animationManager.draw(window, x, y);
}

FloatRect Entity::getRect() const {
    return {x, y, w, h};
}

void Entity::option(const string &name, float speed, int health, const string &initAnimationName) {

    this->name = name;

    if (!initAnimationName.empty()) animationManager.setCurrentAnimation(initAnimationName);

    w = animationManager.getCurrentAnimationWidth();
    h = animationManager.getCurrentAnimationHeight();

    dx = speed;

    this->health = health;
}

int Entity::getHealth() const {
    return health;
}

float Entity::getDy() const {
    return dy;
}

void Entity::setDx(float dx) {
    this->dx = dx;
}

void Entity::setDy(float dy) {
    this->dy = dy;
}

void Entity::setHealth(int health) {
    this->health = health;
}

bool Entity::isAlive() const {
    return alive;
}

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}
