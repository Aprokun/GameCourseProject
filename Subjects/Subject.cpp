//
// Created by lagri on 10.05.2022.
//

#include "Subject.h"

Subject::Subject(AnimationManager &a, float x, float y) {
    animationManager = a;
    this->x = x;
    this->y = y;
    w = animationManager.getCurrentAnimationWidth();
    h = animationManager.getCurrentAnimationHeight();
}

FloatRect Subject::getRect() const {
    return {x, y, w, h};
}

void Subject::draw(RenderWindow &window) {
    animationManager.draw(window, x, y);
}
