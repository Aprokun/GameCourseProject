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
#include "../TinyXML2/tinyxml2.h"

using namespace std;
using namespace sf;
using namespace tinyxml2;

struct Object {
    int getPropertyInt(const string &name);

    float getPropertyFloat(const string &name);

    string getPropertyString(const string &name);

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
    bool loadFromXmlFile(const string &filename);

    bool loadFromString(const string &levelString);

    Object getObject(const string &name);

    vector<Object> getObjects(const string &name);

    vector<Object> getAllObjects();

    void draw(RenderWindow &window);

    Vector2i getTileSize() const;
};


#endif //SFMLTRAIN_LEVEL_H
