#pragma once

#include <SDL2/SDL.h>

#include "geometry.h"
#include "level.h"

class Camera {
public:
    Camera();
    void render(SDL_Renderer* renderer, const Level& level);

    void absoluteToView(int& x, int& y);
    void viewToAbsolute(int& x, int& y);
    void move(int x, int y);
    void resize(unsigned w, unsigned h);

protected:
    Rect mRect;
};