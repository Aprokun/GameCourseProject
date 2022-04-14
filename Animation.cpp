//
// Created by lagri on 04.04.2022.
//

#include "Animation.h"


Animation::Animation(
        Texture &t, int x, int y,
        int w, int h, int count,
        float speed, bool isFlip,
        bool isPlaying, int step) {

    sprite.setTexture(t);

    currentFrame = 0;
    this->speed = speed;
    this->isPlaying = isPlaying;
    this->isFlip = isFlip;

    for (unsigned i = 0; i < count; ++i) {
        frames.emplace_back(x + i * step, y, w, h);
        flipFrames.emplace_back(x + i * step + w, y, -w, h);
    }
}

/* Обновляет анимацию в зависимости от времени.
   time - время */
void Animation::update(float time) {
    // если анимация не играет, то выходим
    if (!isPlaying) return;

    // вычисляем текущий кадр
    currentFrame += speed * time;

    unsigned long long int framesSize = frames.size();
    // если номер текущего фрагмента анимации
    // превышает общее количество фрагментов,
    // то обнуляем номер текущего фрагмента
    if (currentFrame > framesSize) currentFrame -= framesSize;

    // текущий фрагмент анимации
    unsigned currentFrameNumber = currentFrame;

    //устанавливаем текущий фрагмент анимации
    if (!isFlip) sprite.setTextureRect(frames[currentFrameNumber]);
    else sprite.setTextureRect(flipFrames[currentFrameNumber]);
}

Animation::Animation() {
    speed = 0.0f;
    currentFrame = 0;
    isFlip = false;
    isPlaying = true;
}

Sprite &Animation::getSprite() {
    return sprite;
}

vector<IntRect> &Animation::getFrames() {
    return frames;
}

vector<IntRect> &Animation::getReverseFrames() {
    return flipFrames;
}

void Animation::setSpeed(float speed) {
    this->speed = speed;
}

void Animation::setIsFlip(bool isReverse) {
    Animation::isFlip = isReverse;
}

void Animation::setIsPlaying(bool isPlaying) {
    Animation::isPlaying = isPlaying;
}

Animation::~Animation() = default;
