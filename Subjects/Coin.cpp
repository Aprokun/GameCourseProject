//
// Created by lagri on 10.05.2022.
//

#include "Coin.h"

Coin::Coin(AnimationManager &a, float x, float y) : Subject(a, x, y) {
    animationManager.setCurrentAnimation("spin");
}

void Coin::update(float time) {
    animationManager.update(time);
}

string Coin::getObjName() {
    return "coin";
}
