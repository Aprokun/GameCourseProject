//
// Created by lagri on 09.04.2022.
//

#include "Entity.h"

Entity::Entity(AnimationManager &a, int x, int y) {

    animationManager = a;

    this->x = x;
    this->y = y;


    timer = 0;

    timerEnd = 0;

    dx = dy = 0;
}

void Entity::draw(RenderWindow &window) {
    animationManager.draw(window, x, y);
}

FloatRect Entity::getRect() {
    return FloatRect(x, y, w, h);
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
    Entity::dx = dx;
}

void Entity::setDy(float dy) {
    Entity::dy = dy;
}

void Entity::setHealth(int health) {
    Entity::health = health;
}
