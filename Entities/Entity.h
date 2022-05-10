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

    void setDx(float dx);

    void setDy(float dy);

    void setHealth(int health);

    [[nodiscard]] float getDy() const;

    FloatRect getRect();

    [[nodiscard]] int getHealth() const;
};


#endif //SFMLTRAIN_ENTITY_H
