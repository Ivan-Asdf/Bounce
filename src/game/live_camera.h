#pragma once
#include "core/camera.h"

class LiveLevel;

class LiveCamera : private Camera {
public:
    void render(SDL_Renderer* renderer, const LiveLevel& terrain);
};