//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ENTITYFACTORY_H
#define SFMLTRAIN_ENTITYFACTORY_H

#include <exception>

#include "entities/Entity.h"
#include "entities/HeroEntity.h"
#include "entities/ZombieEntity.h"
#include "entities/SlimeEntity.h"

class EntityFactory {
public:
    enum EntityType {
        HERO, ZOMBIE, SLIME
    };

    Entity *getEntity(EntityType type);
};


#endif //SFMLTRAIN_ENTITYFACTORY_H
