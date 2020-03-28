#pragma once
#include <vector>

#include <SDL2/SDL.h>

#include "game_object.h"

#define TILE_SIZE 64

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
    void onClick(int x, int y, int button);

    void render();
    void setRenderer(SDL_Renderer* r);
    void moveCamera(int x, int y);
    void resizeCamera(unsigned w, unsigned h);
    void onKeyDown(SDL_Keycode sym);

private:
    void renderModeLabel();

private:
    EditMode mode;
    Terrain mTerrain;
    Camera mCamera;
    SDL_Renderer* mRenderer;
};