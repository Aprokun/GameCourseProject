//
// Created by lagri on 04.04.2022.
//

#include "AnimationManager.h"

AnimationManager::AnimationManager() = default;

void AnimationManager::setCurrentAnimation(const string &currentAnimation) {
    this->currentAnimation = currentAnimation;
}

void AnimationManager::draw(RenderWindow &window, int x, int y) {

    nameAnimation[currentAnimation].getSprite().setPosition(x, y);

    window.draw(nameAnimation[currentAnimation].getSprite());
}

void AnimationManager::flip(bool flip) {
    nameAnimation[currentAnimation].setIsFlip(flip);
}

void AnimationManager::update(float time) {
    nameAnimation[currentAnimation].update(time);
}

float AnimationManager::getCurrentAnimationHeight() {
    return nameAnimation[currentAnimation].getFrames()[0].height;
}

float AnimationManager::getCurrentAnimationWidth() {
    return nameAnimation[currentAnimation].getFrames()[0].width;
}

void AnimationManager::loadFromXml(const string &fileName, Texture &t) {

    XMLDocument animFile;
    animFile.LoadFile(fileName.c_str());

    XMLElement *head = animFile.FirstChildElement("sprites");

    XMLElement *animElement = head->FirstChildElement("animation");
    while (animElement) {

        Animation animation;

        currentAnimation = animElement->Attribute("title");

        int delay = atoi(animElement->Attribute("delay"));

        animation.setSpeed(1.0 / delay);

        animation.getSprite().setTexture(t);

        XMLElement *cut = animElement->FirstChildElement("cut");
        while (cut) {
            int x = atoi(cut->Attribute("x")),
                    y = atoi(cut->Attribute("y")),
                    w = atoi(cut->Attribute("w")),
                    h = atoi(cut->Attribute("h"));

            animation.getFrames().emplace_back(x, y, w, h);
            animation.getFlipFrames().emplace_back(x + w, y, -w, h);

            cut = cut->NextSiblingElement("cut");
        }

        animation.getSprite().setOrigin(0, 0);

        nameAnimation[currentAnimation] = animation;
        animElement = animElement->NextSiblingElement("animation");
    }
}
