//
// Created by lagri on 04.04.2022.
//

#ifndef SFMLTRAIN_ANIMATIONMANAGER_H
#define SFMLTRAIN_ANIMATIONMANAGER_H

#include <map>
#include <string>
#include "Animation.h"

using namespace std;

enum AnimType {
    STAY, WALK, JUMP
};

class AnimationManager {
private:
    map<string, Animation> nameAnimation;
    string currentAnimation;
public:
    AnimationManager();

    void create(const string &name, Texture &t, int x, int y,
                int w, int h, int count, float speed, int step,
                bool isFlip, bool isPlaying);

    void draw(RenderWindow &window, int x = 0, int y = 0);

    void setCurrentAnimation(const string &currentAnimation);

    void flip(bool flip);

    void update(float time);

    void pause();

    void play();

    float getCurrentAnimationHeight();

    float getCurrenctAnimationWidth();
};


#endif //SFMLTRAIN_ANIMATIONMANAGER_H
