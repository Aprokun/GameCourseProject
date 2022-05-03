//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_BIGBAMBONI_H
#define SFMLTRAIN_BIGBAMBONI_H

#include "Entity.h"

class BigBamboni : public Entity {
public:
    BigBamboni(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;

    string getObjName() override;

    string getName() override;
};


#endif //SFMLTRAIN_BIGBAMBONI_H
