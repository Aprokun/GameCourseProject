//
// Created by lagri on 04.04.2022.
//

#ifndef SFMLTRAIN_ANIMATIONMANAGER_H
#define SFMLTRAIN_ANIMATIONMANAGER_H

#include <map>
#include <string>
#include "Animation.h"
#include "../TinyXML2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class AnimationManager {
private:
    map<string, Animation> nameAnimation;

    string currentAnimation;

public:
    AnimationManager();

    void draw(RenderWindow &window, int x = 0, int y = 0);

    void setCurrentAnimation(const string &currentAnimation);

    void flip(bool flip);

    void update(float time);

    float getCurrentAnimationHeight();

    float getCurrentAnimationWidth();

    void loadFromXml(const string &fileName, Texture &t);
};


#endif //SFMLTRAIN_ANIMATIONMANAGER_H
