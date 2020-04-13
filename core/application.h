#pragma once

#include <SDL2/SDL.h>

#include "event_dispatcher.h"

class Application : public EventHandler {
public:
    Application();
    void handleEvent(SDL_Event event);

    void start();

protected:
    virtual void update() = 0;
    virtual void render() = 0;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};