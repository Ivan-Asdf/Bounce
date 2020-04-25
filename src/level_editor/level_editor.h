#pragma once
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "core/application.h"
#include "core/camera.h"
#include "core/game_object.h"

#include "editable_level.h"
#include "level_camera.h"

enum EditMode {
    ERASE,
    TILE,
    BALL,
};

class LevelEditor : public Application {
public:
    LevelEditor();

    void handleEvent(SDL_Event event);
    void start();

    void onClick(int x, int y, int button);
    void update();
    void render();

    void loadLevelFile(const char* path);
    void saveLevelFile(const char* path);

private:
    void renderModeLabel();

private:
    EditMode mode = TILE;
    EditableLevel mLevelData;
    LevelCamera mCamera;
    TTF_Font* mLabelFont;
};
