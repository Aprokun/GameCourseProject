//
// Created by lagri on 09.04.2022.
//

#include "EntityFactory.h"

Entity *EntityFactory::getEntity(EntityFactory::EntityType type) {
    if (type == EntityType::HERO) {
        return new HeroEntity();
    } else if (type == EntityType::ZOMBIE) {
        return new ZombieEntity();
    } else if (type == EntityType::SLIME) {
        return new SlimeEntity();
    }
    return nullptr;
}
