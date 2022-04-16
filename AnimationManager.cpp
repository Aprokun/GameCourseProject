//
// Created by lagri on 04.04.2022.
//

#include "AnimationManager.h"

AnimationManager::AnimationManager() = default;

void AnimationManager::create(
        const string &name, Texture &t, int x, int y,
        int w, int h, int count, float speed, int step,
        bool isFlip, bool isPlaying) {

    nameAnimation[name] = Animation(t, x, y, w, h, count, speed, step);
}

void AnimationManager::setCurrentAnimation(const string &currentAnimation) {
    this->currentAnimation = currentAnimation;
}

void AnimationManager::draw(RenderWindow &window, int x, int y) {
    nameAnimation[currentAnimation].getSprite().setPosition(x, y);
    window.draw(nameAnimation[currentAnimation].getSprite());
}

void AnimationManager::flip(bool flip) {
    nameAnimation[currentAnimation].setIsFlip(flip);
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
