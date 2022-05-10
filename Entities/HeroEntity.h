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
    bool hit, flip, hasKey;

    unsigned coins;

    Dir currentMoveDir;

    enum State {
        STAY, WALK, JUMP
    } currentState;

    map<string, bool> keys;

    void handleKey();

    void collision(int num);

    void handleAnimation(float time);

public:

    HeroEntity(AnimationManager &a, Level &level, int x, int y);

    bool isHit() const;

    void setIsHit(bool isHit);

    bool isHasKey() const;

    void setHasKey(bool hasKey);

    void update(float time) override;

    void setKeyValue(const string &key, bool value);

    string getObjName() override;

    string getName() override;

    unsigned int getCoins() const;

    void setCoins(unsigned int coins);

    Dir getCurrentMoveDir() const;
};


#endif //SFMLTRAIN_HEROENTITY_H
