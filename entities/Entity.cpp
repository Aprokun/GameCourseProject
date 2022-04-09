//
// Created by lagri on 09.04.2022.
//

#include "Entity.h"

#include <utility>

Entity::Entity(AnimationManager &A, int x, int y) {
    animationManager = A;
    this->x = x;
    this->y = y;
    dir = 0;

    life = true;
    timer = 0;
    timerEnd = 0;
    dx = dy = 0;
}

void Entity::draw(RenderWindow &window) {
    animationManager.draw(window, x, y + h);
}

FloatRect Entity::getRect() const {
    return {x, y, w, h};
}

void Entity::option(string name, float speed, int health, string initAnimationName) {
    this->name = std::move(name);
    if (!initAnimationName.empty()) animationManager.setCurrentAnimation(initAnimationName);
    w = animationManager.getW();
    h = animationManager.getH();
    dx = speed;
    this->health = health;
}