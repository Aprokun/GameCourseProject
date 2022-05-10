//
// Created by lagri on 10.05.2022.
//

#include "SubjectFactory.h"

SubjectFactory::SubjectFactory(Level &currentLevel) {
    this->currentLevel = currentLevel;
}

Subject *SubjectFactory::getSubject(SubjectFactory::SubjectType type, AnimationManager &a, int x, int y) {

    if (type == SubjectType::COIN) {

        return new Coin(a, x, y);

    } else if (type == SubjectType::KEY) {

        return new Key(a, x, y);

    } else if (type == SubjectType::PADLOCK) {

        return new Padlock(a, x, y);

    }

    return nullptr;
}
