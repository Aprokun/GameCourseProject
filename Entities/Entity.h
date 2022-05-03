//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_ENTITY_H
#define SFMLTRAIN_ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../Level.h"
#include "../AnimationManager.h"
#include "../Camera.h"

using namespace std;
using namespace sf;

class Entity {
protected:

    float x{}, y{}, dx{}, dy{}, w{}, h{};

    AnimationManager animationManager;

    vector<Object> objects;

    string name;

    bool live{}, dir{};

    float timer{}, timerEnd{};

    int health{};

    void option(const string &name, float speed = 0, int health = 10, const string &initAnimationName = "");

public:
    Entity() {}

    bool isLive() const;

    Entity(AnimationManager &a, int x, int y);

    virtual void update(float time) = 0;

    virtual string getObjName() = 0;

    virtual string getName() = 0;

    void draw(RenderWindow &window);

    void setKeyValue(const string &key, bool value);

    float getX() const;

    float getY() const;

    void setX(float x);

    void setY(float y);

    void setDx(float dx);

    void setDy(float dy);

    void setDir(bool dir);

    void setHealth(int health);

    float getDx() const;

    float getDy() const;

    bool isDir() const;

    FloatRect getRect();

    int getHealth() const;
};


#endif //SFMLTRAIN_ENTITY_H
