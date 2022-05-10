//
// Created by lagri on 10.05.2022.
//

#ifndef SFMLTRAIN_SUBJECT_H
#define SFMLTRAIN_SUBJECT_H

#include "../AnimationManager.h"

class Subject {
protected:
    float x, y, w, h;

    AnimationManager animationManager;

public:
    Subject(AnimationManager &a, float x, float y);

    virtual string getObjName() = 0;

    virtual void update(float time) = 0;

    [[nodiscard]] FloatRect getRect() const;

    void draw(RenderWindow &window);
};


#endif //SFMLTRAIN_SUBJECT_H
