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

    live = true;
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
    if (!initAnimationName.empty()) animationManager.setCurrentAnimation(initAnimationName);
    w = animationManager.getCurrentAnimationWidth();
    h = animationManager.getCurrentAnimationHeight();
    dx = speed;
    this->health = health;
}

float Entity::getX() const {
    return x;
}

float Entity::getY() const {
    return y;
}

int Entity::getHealth() const {
    return health;
}

float Entity::getDx() const {
    return dx;
}

float Entity::getDy() const {
    return dy;
}

bool Entity::isDir() const {
    return dir;
}

void Entity::setX(float x) {
    Entity::x = x;
}

void Entity::setY(float y) {
    Entity::y = y;
}

void Entity::setDx(float dx) {
    Entity::dx = dx;
}

void Entity::setDy(float dy) {
    Entity::dy = dy;
}

void Entity::setDir(bool dir) {
    Entity::dir = dir;
}

void Entity::setHealth(int health) {
    Entity::health = health;
}

bool Entity::isLive() const {
    return live;
}
