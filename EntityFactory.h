//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ENTITYFACTORY_H
#define SFMLTRAIN_ENTITYFACTORY_H

#include <exception>

#include "entities/Entity.h"
#include "entities/HeroEntity.h"
#include "entities/SmallBamboni.h"
#include "entities/BigBamboni.h"

class EntityFactory {
private:
    Level currentLevel;
public:
    enum EntityType {
        HERO, BIGBAMBONI, SMALLBAMBONI
    };

    explicit EntityFactory(Level &currentLevel);

    Entity *getEntity(EntityType type, AnimationManager &a, int x, int y);
};


#endif //SFMLTRAIN_ENTITYFACTORY_H
