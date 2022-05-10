//
// Created by lagri on 09.04.2022.
//

#include "EntityFactory.h"

Entity *EntityFactory::getEntity(EntityFactory::EntityType type, AnimationManager &a, int x, int y) {
    if (type == EntityType::SMALLBAMBONI) {
        return new SmallBamboni(a, currentLevel, x, y);
    } else if (type == EntityType::BIGBAMBONI) {
        return new BigBamboni(a, currentLevel, x, y);
    }
    return nullptr;
}

EntityFactory::EntityFactory(Level &currentLevel) {
    this->currentLevel = currentLevel;
}
