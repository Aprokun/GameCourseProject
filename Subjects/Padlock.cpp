//
// Created by lagri on 10.05.2022.
//

#include "Padlock.h"

Padlock::Padlock(AnimationManager &a, float x, float y) : Subject(a, x, y) {
    animationManager.setCurrentAnimation("stay");
}

void Padlock::update(float time) {

    animationManager.update(time);
}

string Padlock::getObjName() {
    return "padlock";
}
