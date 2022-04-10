//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ZOMBIEENTITY_H
#define SFMLTRAIN_ZOMBIEENTITY_H

#include "Entity.h"

class ZombieEntity : public Entity {
public:
    ZombieEntity(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;
};


#endif //SFMLTRAIN_ZOMBIEENTITY_H
