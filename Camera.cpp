//
// Created by lagri on 03.04.2022.
//

#include "Camera.h"

View Camera::getPlayerCoordinateForView(float x, float y) {
    view.setCenter(x, y);
    return view;
}

const View &Camera::getView() const {
    return view;
}

void Camera::reset(FloatRect fr) {
    view.reset(fr);
}
