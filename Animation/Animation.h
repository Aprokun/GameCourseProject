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
    vector<IntRect> frames, flipFrames;
    float currentFrame, speed;
    bool isFlip, isPlaying;
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
        flip - true, если это обратная анимация (для правой -> левая, для вверх -> вниз), иначе - false
        isPlaying - true, если анимация проигрывается, иначе - false
    */
    Animation(Texture &t, int x, int y, int w, int h, int count, float speed, int step);

    void update(float time);

    void setSpeed(float speed);

    void setIsFlip(bool isReverse);

    Sprite &getSprite();

    vector<IntRect> &getFrames();

    vector<IntRect> &getFlipFrames();

    void setIsPlaying(bool isPlaying);

    ~Animation();
};


#endif //SFMLTRAIN_ANIMATION_H
