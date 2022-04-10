//
// Created by lagri on 09.04.2022.
//

#ifndef SFMLTRAIN_LEVEL_H
#define SFMLTRAIN_LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TinyXML/tinyxml.h"

using namespace std;
using namespace sf;

struct Object {
    int getPropertyInt(const std::string &name);

    float getPropertyFloat(const std::string &name);

    string getPropertyString(const std::string &name);

    string name;
    string type;
    Rect<float> rect;
    map<string, string> properties;

    Sprite sprite;
};

struct Layer {
    int opacity;
    vector<Sprite> tiles;
};

class Level {
private:
    int width, height, tileWidth, tileHeight;
    int firstTileId;
    Rect<float> drawingBounds;
    Texture tilesetImage;
    vector<Object> objects;
    vector<Layer> layers;
public:
    bool loadFromFile(const std::string &filename);

    Object getObject(std::string name);

    vector<Object> getObjects(std::string name);

    vector<Object> getAllObjects();

    void draw(sf::RenderWindow &window);

    Vector2i getTileSize();
};


#endif //SFMLTRAIN_LEVEL_H
