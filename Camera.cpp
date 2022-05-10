//
// Created by lagri on 03.04.2022.
//

#include "Camera.h"

const View &Camera::getView() const {
    return view;
}

Camera::Camera(FloatRect rect) {
    view = View(rect);
}

void Camera::setCenter(float x, float y) {
    view.setCenter(x, y);
}
