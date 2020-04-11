#pragma once
#include <vector>

#include "game_object.h"

class Terrain {
public:
    void addObject(GameObject* object);
    void removeObjectAt(int x, int y);
    void saveAs(const char* path);
    void load(const char* path);

    friend class Camera;

private:
    int objectAt(int x, int y) const;

protected:
    std::vector<GameObject*> mObjects;
};