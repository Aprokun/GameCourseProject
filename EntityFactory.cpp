//
// Created by lagri on 09.04.2022.
//

#include "EntityFactory.h"

Entity *EntityFactory::getEntity(EntityFactory::EntityType type, AnimationManager &a, int x, int y) {
    if (type == EntityType::HERO) {
        return new HeroEntity(a, currentLevel, x, y);
    } else if (type == EntityType::ZOMBIE) {
        return new ZombieEntity(a, currentLevel, x, y);
    } else if (type == EntityType::SLIME) {
        return new SlimeEntity(a, currentLevel, x, y);
    }
    return nullptr;
}

EntityFactory::EntityFactory(Level &currentLevel) {
    this->currentLevel = currentLevel;
}
