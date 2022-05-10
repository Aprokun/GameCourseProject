//
// Created by lagri on 10.05.2022.
//

#ifndef SFMLTRAIN_SUBJECTFACTORY_H
#define SFMLTRAIN_SUBJECTFACTORY_H

#include "Subjects/Coin.h"
#include "Subjects/Key.h"
#include "Subjects/Padlock.h"

class SubjectFactory {
private:
    Level currentLevel;

public:
    enum SubjectType {
        COIN, KEY, PADLOCK
    };

    explicit SubjectFactory(Level &currentLevel);

    Subject *getSubject(SubjectType type, AnimationManager &a, int x, int y);
};


#endif //SFMLTRAIN_SUBJECTFACTORY_H
