#pragma once

#include <SDL2/SDL.h>

#include "core/event_dispatcher.h"

#include "core/camera.h"

class LevelCamera : public Camera, public EventHandler {
public:
    LevelCamera();
    void render(SDL_Renderer* renderer, const Level& level);

    void handleEvent(SDL_Event event);
};