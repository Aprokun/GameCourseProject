//
// Created by lagri on 04.04.2022.
//

#include "AnimationManager.h"

AnimationManager::AnimationManager() = default;

void AnimationManager::create(
        const string &animationName, Texture &t, int x, int y,
        int w, int h, int count, float speed, int step, bool loop) {
    Animation a;
    a.setSpeed(speed);
    a.getSprite().setTexture(t);
    a.getSprite().setOrigin(0, h);
    a.setIsLoop(loop);
    a.setIsPlaying(false);

    for (unsigned i = 0; i < count; ++i) {
        a.getFrames().emplace_back(x + i * step, y, w, h);
        a.getReverseFrames().emplace_back(x + i * step + w, y, -w, h);
    }

    nameAnimation[animationName] = a;

    currentAnimation = animationName;
}

void AnimationManager::setCurrentAnimation(const string &currentAnimation) {
    AnimationManager::currentAnimation = currentAnimation;
}

void AnimationManager::draw(RenderWindow &window, int x, int y) {
    nameAnimation[currentAnimation].getSprite().setPosition(x, y);
    window.draw(nameAnimation[currentAnimation].getSprite());
}

void AnimationManager::reverse(bool reverse) {
    nameAnimation[currentAnimation].setIsReverse(reverse);
}

void AnimationManager::update(float time) {
    nameAnimation[currentAnimation].update(time);
}

void AnimationManager::pause() {
    nameAnimation[currentAnimation].setIsPlaying(false);
}

void AnimationManager::play() {
    nameAnimation[currentAnimation].setIsPlaying(true);
}

float AnimationManager::getCurrentAnimationHeight() {
    return nameAnimation[currentAnimation].getFrames()[0].height;
}

float AnimationManager::getCurrenctAnimationWidth() {
    return nameAnimation[currentAnimation].getFrames()[0].width;
}
