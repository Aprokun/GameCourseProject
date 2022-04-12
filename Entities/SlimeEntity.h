//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_SLIMEENTITY_H
#define SFMLTRAIN_SLIMEENTITY_H

#include "Entity.h"

class SlimeEntity : public Entity {
public:
    SlimeEntity(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;
};


#endif //SFMLTRAIN_SLIMEENTITY_H
