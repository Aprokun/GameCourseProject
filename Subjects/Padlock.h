//
// Created by lagri on 10.05.2022.
//

#ifndef SFMLTRAIN_PADLOCK_H
#define SFMLTRAIN_PADLOCK_H

#include "Subject.h"

class Padlock : public Subject {
public:
    Padlock(AnimationManager &a, float x, float y);

    void update(float time) override;

    string getObjName() override;
};


#endif //SFMLTRAIN_PADLOCK_H
