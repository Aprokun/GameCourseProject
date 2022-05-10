//
// Created by lagri on 04.04.2022.
//

#include "Animation.h"

Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float speed, int step) {

    sprite.setTexture(t);

    currentFrame = 0;

    this->speed = speed;

    this->isFlip = false;

    for (unsigned i = 0; i < count; ++i) {
        frames.emplace_back(x + i * step, y, w, h);
        flipFrames.emplace_back(x + i * step + w, y, -w, h);
    }
}

/* Обновляет анимацию в зависимости от времени.
   time - время */
void Animation::update(float time) {

    // Вычисляем текущий кадр
    currentFrame += speed * time;

    unsigned long long int framesSize = frames.size();

    // Если номер текущего фрагмента анимации
    // превышает общее количество фрагментов,
    // то обнуляем номер текущего фрагмента
    if (currentFrame > framesSize) currentFrame -= framesSize;

    // Текущий фрагмент анимации
    unsigned currentFrameNumber = currentFrame;

    // Устанавливаем текущий фрагмент анимации
    if (!isFlip) {
        sprite.setTextureRect(frames[currentFrameNumber]);
    } else {
        sprite.setTextureRect(flipFrames[currentFrameNumber]);
    }
}

Animation::Animation() {

    speed = 0.0f;
    currentFrame = 0;
    isFlip = false;
}

Sprite &Animation::getSprite() {
    return sprite;
}

vector<IntRect> &Animation::getFrames() {
    return frames;
}

vector<IntRect> &Animation::getFlipFrames() {
    return flipFrames;
}

void Animation::setSpeed(float speed) {
    this->speed = speed;
}

void Animation::setIsFlip(bool isReverse) {
    Animation::isFlip = isReverse;
}

Animation::~Animation() = default;
