#include "assert.h"

#include "application.h"
#include "globals.h"
#include "texture_loader.h"

static void capFramerate(Uint32 startTick) {
    if ((1000 / FPS) > SDL_GetTicks() - startTick)
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTick));
}

Application::Application() {
    int rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc)
        printf("Failed to initialize SDL2. Error: %d\n", rc);
    SDL_Window* mWindow =
        SDL_CreateWindow("Bounce game", 300, 300, 13 * TILE_SIZE, 8 * TILE_SIZE,
                         SDL_WINDOW_RESIZABLE);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    TextureLoader::init(mRenderer);

    EventDispatcher::subscribe(this, SDL_QUIT);
}

void Application::handleEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
    }
}

void Application::start() {
    Uint32 startFrameTime;
    while (true) {
        startFrameTime = SDL_GetTicks();
        EventDispatcher::pollEvents();
        update();
        render();
        capFramerate(startFrameTime);
    }
}