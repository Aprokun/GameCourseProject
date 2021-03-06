//
// Created by lagri on 03.04.2022.
//

#ifndef SFMLTRAIN_CAMERA_H
#define SFMLTRAIN_CAMERA_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Camera {
private:
    View view;

public:
    explicit Camera(FloatRect rect);

    const View &getView() const;

    void setCenter(float x, float y);
};


#endif //SFMLTRAIN_CAMERA_H
