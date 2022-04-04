//
// Created by lagri on 04.04.2022.
//

#include "AnimationManager.h"

AnimationManager::AnimationManager() = default;

void AnimationManager::create(
        string animationName, Texture &t, int x, int y,
        int w, int h, int count, int speed, int step, bool loop) {
    Animation a;
    a.setSpeed(speed);
    a.getSprite().setTexture(t);
    a.getSprite().setOrigin(0, h);
    a.setIsLoop(loop);

    for (unsigned i = 0; i < count; ++i) {
        a.getFrames().push_back(IntRect(x + i * step, y, w, h));
        a.getReverseFrames().push_back(IntRect(x + i * step + w, y, -w, h));
    }

    nameToAnimation[animationName] = a;

    currentAnimation = animationName;
}
