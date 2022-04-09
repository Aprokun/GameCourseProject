//
// Created by lagri on 03.04.2022.
//

#include "HeroEntity.h"

void HeroEntity::update(float time) {
    currentMoveDir = keyCheck();


}

Dir HeroEntity::keyCheck() {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        return LEFT;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        return UP;
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        return RIGHT;
    } else if (Keyboard::isKeyPressed(Keyboard::S)) {
        return DOWN;
    }
}
