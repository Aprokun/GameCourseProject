//
// Created by lagri on 10.05.2022.
//

#ifndef SFMLTRAIN_COIN_H
#define SFMLTRAIN_COIN_H

#include "Subject.h"
#include "../Level/Level.h"

class Coin : public Subject {
public:
    Coin(AnimationManager &a, float x, float y);

    void update(float time) override;

    string getObjName() override;
};


#endif //SFMLTRAIN_COIN_H
