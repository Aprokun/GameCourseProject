//
// Created by lagri on 10.05.2022.
//

#ifndef SFMLTRAIN_KEY_H
#define SFMLTRAIN_KEY_H

#include "Subject.h"

class Key : public Subject {
public:
    Key(AnimationManager &a, float x, float y);

    void update(float time) override;

    string getObjName() override;
};


#endif //SFMLTRAIN_KEY_H
