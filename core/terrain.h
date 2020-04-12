#pragma once
#include <vector>

#include "game_object.h"

typedef std::vector<GameObject*> GameObjects;

class LevelData {
public:
    // Read-only for Camera to use to render
    const GameObjects& getGameObjects() const;

    // Used by LevelEditor
    void addObject(GameObject* object);
    void removeObjectAt(int x, int y);
    void saveAs(const char* path);

    // Used by LevelEditor & LiveLevelData(child)
    void load(const char* path);

private:
    int objectAt(int x, int y) const;

protected:
    GameObjects mObjects;
};