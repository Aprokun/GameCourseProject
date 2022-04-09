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
    map<string, Animation> nameAnimation;
    string currentAnimation;
public:
    AnimationManager();

    void
    create(const string &animationName, Texture &t, int x, int y, int w, int h, int count, float speed, int step = 0,
           bool loop = true);

    void draw(RenderWindow &window, int x = 0, int y = 0);

    void setCurrentAnimation(const string &currentAnimation);

    void reverse(bool reverse);

    void update(float time);

    void pause();

    void play();
};


#endif //SFMLTRAIN_ANIMATIONMANAGER_H
