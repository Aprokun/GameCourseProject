//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ENTITY_H
#define SFMLTRAIN_ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../Level/Level.h"
#include "../Animation/AnimationManager.h"
#include "../Camera.h"

using namespace std;
using namespace sf;

class Entity {
protected:
    float x{}, y{}, dx{}, dy{}, w{}, h{};

    bool alive;

    AnimationManager animationManager;

    vector<Object> objects;

    string name;

    float timer{}, timerEnd{};

    int health{};

    void option(const string &name, float speed = 0, int health = 10, const string &initAnimationName = "");

public:
    Entity() = default;

    Entity(AnimationManager &a, int x, int y);

    virtual void update(float time) = 0;

    virtual string getObjName() = 0;

    void draw(RenderWindow &window);

    [[nodiscard]] bool isAlive() const;

    void setDx(float dx);

    void setDy(float dy);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    void setHealth(int health);

    [[nodiscard]] float getDy() const;

    [[nodiscard]] FloatRect getRect() const;

    [[nodiscard]] int getHealth() const;
};


#endif //SFMLTRAIN_ENTITY_H
