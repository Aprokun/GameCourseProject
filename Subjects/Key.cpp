//
// Created by lagri on 10.05.2022.
//

#include "Key.h"

Key::Key(AnimationManager &a, float x, float y) : Subject(a, x, y) {
    animationManager.setCurrentAnimation("stay");
}

void Key::update(float time) {
    animationManager.update(time);
}

string Key::getObjName() {
    return "key";
}
