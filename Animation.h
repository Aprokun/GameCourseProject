//
// Created by lagri on 04.04.2022.
//

#ifndef SFMLTRAIN_ANIMATION_H
#define SFMLTRAIN_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class Animation {
private:
    vector<IntRect> frames, reverseFrames;
    float currentFrame, speed;
    bool isReverse, isPlaying, isLoop;
    Sprite sprite;
public:
    Animation();

    /*  Конструктор для анимации.
        t - текстура анимации
        x - начальная позиция фрагмента анимации по иксу
        y - начальная позиция фрагмента анимации по игреку
        w - длина фрагмента анимации
        h - высота фрагмента анимации
        count - количество фрагментов анимации
        speed - скорость анимации
        reverse - true, если это обратная анимация (для правой -> левая, для вверх -> вниз), иначе - false
        playing - true, если анимация проигрывается, иначе - false
    */
    Animation(Texture &t, int x, int y, int w, int h, int count, float speed, bool reverse, bool playing, int step);

    void update(float time);

    void setIsLoop(bool isLoop);

    void setSpeed(float speed);

    void setIsReverse(bool isReverse);

    Sprite &getSprite();

    vector<IntRect> &getFrames();

    vector<IntRect> &getReverseFrames();

    ~Animation();

    void setIsPlaying(bool isPlaying);
};


#endif //SFMLTRAIN_ANIMATION_H
