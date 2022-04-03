//
// Created by lagri on 03.04.2022.
//

#include "Hero.h"

Hero::Hero(float startPosX, float startPosY, int widthSprite,
           int heightSprite, float moveSpeed, const string &imageFilePath) {
    x = startPosX, y = startPosY;
    dx = dy = 0;
    this->widthSprite = widthSprite;
    this->heightSprite = heightSprite;
    this->moveSpeed = moveSpeed;
    this->currentMoveFrame = 0.0f;

    image.loadFromFile(imageFilePath);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(
            IntRect(0, 0, this->widthSprite, this->heightSprite)
    );
    sprite.setPosition(x, y);

    camera.reset(FloatRect(0, 0, 640, 480));
}

Hero::Hero() = default;

void Hero::update(float time) {
    switch (curDir) {
        case UP: {
            dx = 0.0, dy = -moveSpeed;
            break;
        }
        case RIGHT: {
            dx = moveSpeed, dy = 0;
            if (currentMoveFrame >= 2) currentMoveFrame -= 2;
            sprite.setScale(-1, 1);
            sprite.setTextureRect(IntRect(24 * int(currentMoveFrame), 0, 24, 25));
            break;
        }
        case DOWN: {
            dx = 0.0, dy = moveSpeed;
            if (currentMoveFrame >= 2) currentMoveFrame -= 2;
            break;
        }
        case LEFT: {
            dx = -moveSpeed, dy = 0;
            if (currentMoveFrame >= 2) currentMoveFrame -= 2;
            sprite.setScale(1, 1);
            sprite.setTextureRect(IntRect(24 * int(currentMoveFrame), 0, 24, 25));
            break;
        }
    }

    x += dx * time;
    y += dy * time;

    moveSpeed = 0;
    sprite.setPosition(x, y);
    camera.getPlayerCoordinateForView(x, y);
}

void Hero::setCurDir(Hero::dir curDir) {
    Hero::curDir = curDir;
}

void Hero::setMoveSpeed(float moveSpeed) {
    Hero::moveSpeed = moveSpeed;
}

const Sprite &Hero::getSprite() const {
    return sprite;
}

void Hero::setCurrentMoveFrame(float currentMoveFrame) {
    Hero::currentMoveFrame = currentMoveFrame;
}

float Hero::getCurrentMoveFrame() const {
    return currentMoveFrame;
}

const Camera &Hero::getCamera() const {
    return camera;
}
