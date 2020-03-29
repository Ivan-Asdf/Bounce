#pragma once
#include <vector>

#include <SDL2/SDL.h>

#include "game_object.h"
#include "terrain.h"

class Camera {
public:
    Camera();
    void render(SDL_Renderer* renderer, const Terrain& terrain);

    void absoluteToView(int& x, int& y);
    void viewToAbsolute(int& x, int& y);
    void move(int x, int y);
    void resize(unsigned w, unsigned h);

private:
    Rect mRect;
};

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
    Terrain mTerrain;
    Camera mCamera;
    SDL_Renderer* mRenderer;
};