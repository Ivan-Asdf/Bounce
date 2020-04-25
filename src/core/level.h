#pragma once
#include <vector>

#include "game_object.h"

typedef std::vector<GameObject*> GameObjects;

class Level {
public:
    // Read-only for Camera to use to render
    const GameObjects& getGameObjects() const;

    // Used by LevelEditor & LiveLevelData(child)
    void load(const char* path);

protected:
    GameObjects mObjects;
};