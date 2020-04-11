#pragma once

#include "geometry.h"
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