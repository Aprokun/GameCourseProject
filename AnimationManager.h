//
// Created by lagri on 04.04.2022.
//

#ifndef SFMLTRAIN_ANIMATIONMANAGER_H
#define SFMLTRAIN_ANIMATIONMANAGER_H

#include <map>
#include <string>
#include "Animation.h"

using namespace std;

class AnimationManager {
private:
    map<string, Animation> nameToAnimation;
    string currentAnimation;
public:
    AnimationManager();

    void create(string animationName, Texture &t, int x, int y, int w, int h, int count, int speed, int step = 0, bool loop = true);
};


#endif //SFMLTRAIN_ANIMATIONMANAGER_H
