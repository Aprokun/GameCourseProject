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

class HeroEntity : public Entity {
private:
    HeroEntity() = default;

    HeroEntity(const HeroEntity &);

    HeroEntity(AnimationManager &a, Level &level, int x, int y);

    HeroEntity &operator=(HeroEntity &);

    bool hit, flip, hasKey;

    unsigned coins;

    int timer;

    enum State {
        STAY, WALK, JUMP
    } currentState;

    map<string, bool> keys;

    void handleKey();

    void collision(int num);

    void handleAnimation(float time);

public:

    static HeroEntity *getInstance(AnimationManager &a, Level &level, int x, int y);

    [[nodiscard]] bool isHit() const;

    void setIsHit(bool isHit);

    void setTimer(int ms);

    [[nodiscard]] bool isHasKey() const;

    void setHasKey(bool hasKey);

    void update(float time) override;

    void setKeyValue(const string &key, bool value);

    string getObjName() override;

    [[nodiscard]] unsigned int getCoins() const;

    void setCoins(unsigned int coins);

};


#endif //SFMLTRAIN_HEROENTITY_H
