//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ENTITY_H
#define SFMLTRAIN_ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../AnimationManager.h"
#include "../Camera.h"

using namespace std;
using namespace sf;

class Entity {
protected:
    float x, y, dx, dy, w, h;
    AnimationManager animationManager;
    vector obj;
    bool life, dir;
    float timer, timerEnd;
    string name;
    int health;

public:
    Entity() {}

    Entity(AnimationManager &A, int x, int y);

    virtual void update(float time) = 0;

    void draw(RenderWindow &window);

    FloatRect getRect() const;

    void option(std::string name, float speed = 0, int health = 10, std::string initAnimationName = "");

};


#endif //SFMLTRAIN_ENTITY_H
