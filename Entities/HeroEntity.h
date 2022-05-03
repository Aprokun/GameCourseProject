//
// Created by lagri on 03.04.2022.
//

#ifndef SFMLTRAIN_HEROENTITY_H
#define SFMLTRAIN_HEROENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "../Camera.h"

using namespace sf;
using namespace std;

enum Dir {
    UP, RIGHT, DOWN, LEFT, NONE
};

class HeroEntity : public Entity {
private:
    bool hit, flip{};
    Dir currentMoveDir;

    enum State {
        STAY, WALK, JUMP
    } currentState;

    map<string, bool> keys;

    void handleKey();

    void collision(int num);

    void handleAnimation(float time);

public:

    bool isHit() const;

    void setIsHit(bool isHit);

    HeroEntity(AnimationManager &a, Level &level, int x, int y);

    void update(float time) override;

    void setKeyValue(const string &key, bool value);

    string getObjName() override;

    string getName() override;

    Dir getCurrentMoveDir() const;
};


#endif //SFMLTRAIN_HEROENTITY_H
