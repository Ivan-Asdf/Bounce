#include <fstream>

#include <yaml-cpp/yaml.h>

#include "globals.h"

#include "terrain.h"

void Terrain::addObject(GameObject* object) {
    if (objectAt(object->getRect().x, object->getRect().y) == -1)
        mObjects.push_back(object);
}

void Terrain::removeObjectAt(int x, int y) {
    int index = objectAt(x, y);
    mObjects.erase(mObjects.begin() + index);
}

namespace YAML {
template <> struct convert<std::vector<GameObject*>> {
    static Node encode(const std::vector<GameObject*>& rhs) {
        Node rootNode;
        for (const GameObject* object : rhs) {
            if (dynamic_cast<const Ball*>(object)) {
                Node node;
                node["x"] = object->mRect.x;
                node["y"] = object->mRect.y;
                rootNode["Balls"].push_back(node);
            } else if (dynamic_cast<const Tile*>(object)) {
                Node node;
                node["x"] = object->mRect.x;
                node["y"] = object->mRect.y;
                rootNode["Tiles"].push_back(node);
            }
        }
        return rootNode;
    }

    static bool decode(const Node& node, std::vector<GameObject*>& rhs) {
        if (!node.IsMap()) {
            puts("wtf its should be a map with Tiles/Balls keys");
            return false;
        }
        if (auto balls = node["Balls"]) {
            for (int i = 0; i < balls.size(); ++i) {
                Node ball = balls[i];
                GameObject* newObject = new Ball(
                    ball["x"].as<int>(), ball["y"].as<int>(), TILE_SIZE);
                rhs.push_back(newObject);
            }
        }
        if (auto tiles = node["Tiles"]) {
            for (int i = 0; i < tiles.size(); ++i) {
                Node tile = tiles[i];
                GameObject* newObject = new Tile(
                    tile["x"].as<int>(), tile["y"].as<int>(), TILE_SIZE);
                rhs.push_back(newObject);
            }
        }
        return true;
    }
};
} // namespace YAML

void Terrain::saveAs(const char* path) {
    YAML::Node node;
    node = mObjects;
    std::ofstream fout(path);
    fout << node;
}
void Terrain::load(const char* path) {
    YAML::Node node = YAML::LoadFile(path);
    mObjects = node.as<std::vector<GameObject*>>();
}

int Terrain::objectAt(int x, int y) const {
    for (int i = 0; i < mObjects.size(); ++i) {
        if (isColliding(x, y, mObjects[i]->getRect())) {
            return i;
        }
    }
    return -1;
}