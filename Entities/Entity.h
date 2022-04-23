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

    bool isAlive{}, dir{};

    // только для hero
    map<string, bool> keys;

    float timer{}, timerEnd{};

    string name;

    int health{};

    void option(string name, float speed = 0, int health = 10, string initAnimationName = "");

    FloatRect getRect();

public:

    Entity() {}

    Entity(AnimationManager &a, int x, int y);

    virtual void update(float time) = 0;

    void draw(RenderWindow &window);

    void setKeyValue(const string &key, bool value);

    float getX() const;

    float getY() const;
};


#endif //SFMLTRAIN_ENTITY_H
