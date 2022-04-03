//
// Created by lagri on 03.04.2022.
//

#ifndef SFMLTRAIN_HERO_H
#define SFMLTRAIN_HERO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Camera.h"

using namespace sf;
using namespace std;

class Hero {
public:
    enum dir {
        UP, RIGHT, DOWN, LEFT
    };
private:
    Image image;
    Texture texture;
    Sprite sprite;
    Camera camera;
    int widthSprite{}, heightSprite{};
    float currentMoveFrame{};
    float moveSpeed{};
    float x{}, y{};
    float dx{}, dy{};
    dir curDir;
public:
    Hero(float startPosX, float startPosY, int widthSprite,
         int heightSprite, float moveSpeed, const string &imageFilePath);

    Hero();

    void setCurrentMoveFrame(float currentMoveFrame);

    float getCurrentMoveFrame() const;

    void setMoveSpeed(float moveSpeed);

    const Sprite &getSprite() const;

    const Camera &getCamera() const;

    void update(float time);

    void setCurDir(dir curDir);
};


#endif //SFMLTRAIN_HERO_H
