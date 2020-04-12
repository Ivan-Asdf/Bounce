#pragma once
#include <vector>

#include <SDL2/SDL.h>

#include "core/camera.h"
#include "core/game_object.h"
#include "core/terrain.h"

enum EditMode {
    ERASE,
    TILE,
    BALL,
};

class LevelEditor {
public:
    LevelEditor(SDL_Renderer* renderer);

    void onClick(int x, int y, int button);
    void render();
    void moveCamera(int x, int y);
    void resizeCamera(unsigned w, unsigned h);
    void onKeyDown(SDL_Keycode sym);

    void loadLevelFile(const char* path);
    void saveLevelFile(const char* path);

private:
    void renderModeLabel();

private:
    EditMode mode = TILE;
    LevelData mLevelData;
    Camera mCamera;
    SDL_Renderer* mRenderer;
    TTF_Font* mLabelFont;
};
