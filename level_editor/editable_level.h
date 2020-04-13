#pragma once

#include "core/level.h"

class EditableLevel : public Level {
public:
    void addObject(GameObject* object);
    void removeObjectAt(int x, int y);

    // Used by LevelEditor
    void saveAs(const char* path);

private:
    int objectAt(int x, int y) const;
};