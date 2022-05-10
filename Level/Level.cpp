//
// Created by lagri on 09.04.2022.
//

#include "Level.h"

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
#if defined(_WIN32)
const char DIR_SEPARATOR = '\\';
#else
const char DIR_SEPARATOR = '/';
#endif

// Returns parent directory of given path;
string GetParentDirectory(const string &filepath) {
    const size_t slashPos = filepath.find_last_of('/');
    string parentDir;
    if (slashPos != string::npos) {
        parentDir = filepath.substr(0, slashPos);
    }
    return parentDir;
}

// Joins two path fragments, e.g. directory path and filename
string JoinPaths(const string &path, const string &subpath) {
    if (path.empty()) {
        return subpath;
    }
    if (subpath.empty()) {
        return path;
    }

    return path + DIR_SEPARATOR + subpath;
}

// Parses hex-encoded RGB like "6d9fb9"
Color ParseColor(const string &hexRGB) {
    char *pEnd = nullptr;
    const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
    if (*pEnd != '\0') {
        throw runtime_error(hexRGB + " is not valid hex-encoded RGB color");
    }

    const auto red = uint8_t((hexValue >> 16) % 256);
    const auto green = uint8_t((hexValue >> 8) % 256);
    const auto blue = uint8_t(hexValue % 256);

    return {red, green, blue};
}

float ParseFloat(const string &str) {
    char *pEnd = nullptr;
    const float value = strtof(str.c_str(), &pEnd);
    if (*pEnd != '\0') {
        throw runtime_error("'" + str + "' is not a float number");
    }

    return value;
}

bool Level::loadFromXmlFile(const string &filename) {
    XMLDocument levelFile;

    // Load XML into in-memory XMLDocument.
    if (levelFile.LoadFile(filename.c_str()) != XML_SUCCESS) {
        throw runtime_error("Loading level \"" + filename + "\" failed.");
    }

    // Element <map> should be root in TMX format.
    XMLElement *map = levelFile.FirstChildElement("map");
    if (map == nullptr) {
        throw runtime_error("<map> element not found");
    }

    // Map element example:
    //   <map version="1.0" orientation="orthogonal"
    //    width="10" height="10" tilewidth="34" tileheight="34">
    width = stoi(map->Attribute("width"));
    height = stoi(map->Attribute("height"));
    tileWidth = stoi(map->Attribute("tilewidth"));
    tileHeight = stoi(map->Attribute("tileheight"));

    // Retrieve tileset description and the first tile GID (Group Identifier).
    XMLElement *tilesetElement = map->FirstChildElement("tileset");
    firstTileId = stoi(tilesetElement->Attribute("firstgid"));

    // <image> contains tileset texture
    XMLElement *image = tilesetElement->FirstChildElement("image");
    const string imageFilename = image->Attribute("source");
    const string imagePath = JoinPaths(GetParentDirectory(filename), imageFilename);

    Color matteColor = Color(0, 0, 0, 0);
    if (image->Attribute("trans") != nullptr) {
        matteColor = ParseColor(image->Attribute("trans"));
    }

    Image img;
    if (!img.loadFromFile(imagePath)) {
        cout << "Failed to load tile sheet." << endl;
        return false;
    }

    // Set tileset matte color, used to composite transparent image on
    //  background filled with matte color.
    img.createMaskFromColor(matteColor);
    // Load texture from file.
    tilesetImage.loadFromImage(img);
    // Keep texture sharp when resized.
    tilesetImage.setSmooth(false);

    // Retrieve amount of rows and columns in tileset.
    const int columns = tilesetImage.getSize().x / tileWidth;
    const int rows = tilesetImage.getSize().y / tileHeight;

    // Collect texture rects list.
    // Each texture rect is subimage in tileset image, i.e. single tile image.
    vector<IntRect> subRects;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            IntRect rect;
            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;
            subRects.push_back(rect);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Parse tile layers
    ///
    XMLElement *layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        // Copy transparency if it set in XML,
        //  or make layer opaque (255).
        if (layerElement->Attribute("opacity") != nullptr) {
            float opacity = ParseFloat(layerElement->Attribute("opacity"));
            layer.opacity = Uint8(255 * opacity);
        } else {
            layer.opacity = 255;
        }

        // <data> contains multiple tiles description.
        XMLElement *layerDataElement = layerElement->FirstChildElement("data");
        if (layerDataElement == nullptr) {
            cout << "Bad map. No layer information found." << endl;
        }

        // <tile> contains single tile description.
        XMLElement *tileElement = layerDataElement->FirstChildElement("tile");
        if (tileElement == nullptr) {
            cout << "Bad map. No tile information found." << endl;
            return false;
        }

        int x = 0;
        int y = 0;
        while (tileElement) {
            const int tileGID = stoi(tileElement->Attribute("gid"));
            const int subRectToUse = tileGID - firstTileId;

            // Figure out texture rect for each tile.
            if (subRectToUse >= 0) {
                Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight));
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

    ////////////////////////////////////////////////////////////////////////////
    /// Collecting objects list.
    ///

    // If there are object layers.
    if (map->FirstChildElement("objectgroup") != nullptr) {
        XMLElement *objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            // Enter into <object> node
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                // Collecting object properties - type, name, position, etc.
                string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                float x = stof(objectElement->Attribute("x"));
                float y = stof(objectElement->Attribute("y"));

                Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(IntRect(0, 0, 0, 0));
                sprite.setPosition(x, y);

                float width, height;
                if (objectElement->Attribute("width") != nullptr) {
                    width = stof(objectElement->Attribute("width"));
                    height = stof(objectElement->Attribute("height"));
                } else {
                    const size_t index = stoi(objectElement->Attribute("gid")) - firstTileId;
                    width = static_cast<float>(subRects[index].width);
                    height = static_cast<float>(subRects[index].height);
                    sprite.setTextureRect(subRects[index]);
                    sprite.setOrigin(0, height);
                }

                // Define object
                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                FloatRect objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // Read object properties
                XMLElement *properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr) {
                    XMLElement *prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            string propertyName = prop->Attribute("name");
                            string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // Add object to list
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        cout << "No object layers found..." << endl;
    }

    return true;
}

vector<Object> Level::getAllObjects() {
    return objects;
}

Object Level::getObject(const string &name) {

    // Только первый объект с заданным именем
    for (auto &object: objects) {

        if (object.name == name) {
            return object;
        }

    }

    return Object();
}

vector<Object> Level::getObjects(const string &name) {

    // Все объекты с заданным именем
    vector<Object> vec;

    for (auto &object: objects) {

        if (object.name == name) {
            vec.push_back(object);
        }

    }

    return vec;
}

Vector2i Level::getTileSize() const {
    return {tileWidth, tileHeight};
}

void Level::draw(RenderWindow &window) {

    // Рисуем все тайлы (объекты НЕ рисуем!)
    for (auto &layer: layers) {

        for (const auto &tile: layer.tiles) {
            window.draw(tile);
        }

    }
}
