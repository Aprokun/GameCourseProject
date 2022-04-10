//
// Created by lagri on 09.04.2022.
//

#include "Level.h"

int Object::getPropertyInt(const std::string &name) {
    return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(const std::string &name) {
    return strtod(properties[name].c_str(), nullptr);
}

string Object::getPropertyString(const std::string &name) {
    return properties[name];
}

bool Level::loadFromFile(const std::string &filename) {
    TiXmlDocument levelFile(filename.c_str());

    if (!levelFile.LoadFile()) {
        cout << "Loading level \"" << filename << "\" failed." << endl;
        return false;
    }

    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileId = atoi(tilesetElement->Attribute("firstgid"));

    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    string imagepath = image->Attribute("source");

    Image img;

    if (!img.loadFromFile(imagepath)) {
        cout << "Failed to load tile sheet." << endl;
        return false;
    }

    img.createMaskFromColor(Color(255, 255, 255));
    tilesetImage.loadFromImage(img);
    tilesetImage.setSmooth(false);

    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    vector<sf::Rect<int> > subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        if (layerElement->Attribute("opacity") != NULL) {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL) {
            cout << "Bad map. No layer information found." << endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL) {
            cout << "Bad map. No tile information found." << endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileId;

            if (subRectToUse >= 0) {
                Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height) {
                    y = 0;
                }
            }
        }

        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }

    TiXmlElement *objectGroupElement;

    if (map->FirstChildElement("objectgroup") != NULL) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL) {
                    objectType = objectElement->Attribute("type");
                }

                std::string objectName;
                if (objectElement->Attribute("name") != NULL) {
                    objectName = objectElement->Attribute("name");
                }

                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileId].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileId].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileId]);
                }

                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);
                objectElement = objectElement->NextSiblingElement("object");
            }

            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object Level::getObject(std::string name) {
    // ������ ������ ������ � �������� ������
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

vector<Object> Level::getObjects(std::string name) {
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            vec.push_back(objects[i]);

    return vec;
}


vector<Object> Level::getAllObjects() {
    return objects;
};


Vector2i Level::getTileSize() {
    return Vector2i(tileWidth, tileHeight);
}

void Level::draw(sf::RenderWindow &window) {
    for (auto &layer: layers) {
        for (const auto &tile: layer.tiles) {
            window.draw(tile);
        }
    }
}