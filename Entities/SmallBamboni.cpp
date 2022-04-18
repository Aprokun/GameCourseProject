//
// Created by lagri on 09.04.2022.
//

#include "SmallBamboni.h"

void SmallBamboni::update(float time) {
    x += dx * time;
    timer += time;

    if (timer > 3200) {
        dx *= -1;
        timer = 0;
    }

    if (health <= 0) {
        animationManager.setCurrentAnimation("dead");
        dx = 0;
        timerEnd += time;
        if (timerEnd > 4000) isAlive = false;
    }

    animationManager.update(time);
}

SmallBamboni::SmallBamboni(AnimationManager &a, Level &level, int x, int y) : Entity(a, x, y) {
    option("SmallBamboni", 0.009f, 1, "walk");
}
