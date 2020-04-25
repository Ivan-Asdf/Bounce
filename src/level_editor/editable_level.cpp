#include <fstream>

#include <yaml-cpp/yaml.h>

#include "core/game_object.h"
#include "core/globals.h"

#include "editable_level.h"

void EditableLevel::addObject(GameObject* object) {
    if (objectAt(object->getRect().x, object->getRect().y) == -1)
        mObjects.push_back(object);
}

void EditableLevel::removeObjectAt(int x, int y) {
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
};
} // namespace YAML

void EditableLevel::saveAs(const char* path) {
    YAML::Node node;
    node = mObjects;
    std::ofstream fout(path);
    fout << node;
}

int EditableLevel::objectAt(int x, int y) const {
    for (int i = 0; i < mObjects.size(); ++i) {
        if (isColliding(x, y, mObjects[i]->getRect())) {
            return i;
        }
    }
    return -1;
}