#pragma once
#include "core/camera.h"

class LiveLevelData;

class LiveCamera : private Camera {
public:
    void render(SDL_Renderer* renderer, const LiveLevelData& terrain);
};