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
    View getPlayerCoordinateForView(float x, float y);

    const View &getView() const;

    void reset(FloatRect fr);
};


#endif //SFMLTRAIN_CAMERA_H
