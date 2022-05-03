//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_SMALLBAMBONI_H
#define SFMLTRAIN_SMALLBAMBONI_H

#include "Entity.h"

class SmallBamboni : public Entity {
public:
    SmallBamboni(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;

    string getObjName() override;

    string getName() override;
};


#endif //SFMLTRAIN_SMALLBAMBONI_H
