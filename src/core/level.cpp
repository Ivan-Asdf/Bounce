#include <yaml-cpp/yaml.h>

#include "globals.h"

#include "level.h"

const GameObjects& Level::getGameObjects() const { return mObjects; }

namespace YAML {
template <> struct convert<std::vector<GameObject*>> {
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

void Level::load(const char* path) {
    YAML::Node node = YAML::LoadFile(path);
    mObjects = node.as<std::vector<GameObject*>>();
}
