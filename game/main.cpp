#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#include <SDL2/SDL_ttf.h>

#include "core/globals.h"
#include "core/texture_loader.h"

#include "game.h"

void capFramerate(Uint32 startTick);

int main() {

    int rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc)
        printf("Failed to initialize SDL2. Error: %d\n", rc);
    TTF_Init();
    SDL_Window* window =
        SDL_CreateWindow("Bounce game", 300, 300, 13 * TILE_SIZE, 8 * TILE_SIZE,
                         SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextureLoader::init(renderer);

    Game game(renderer);
    game.loadLevelFile("level.yaml");

    SDL_Event event;
    bool quit = false;
    Uint32 startFrameTime;
    while (!quit) {
        startFrameTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_WINDOWEVENT) {

            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    game.movePlayerBall(0, -1);
                    break;
                case SDLK_DOWN:
                    game.movePlayerBall(0, 1);
                    break;
                case SDLK_LEFT:
                    game.movePlayerBall(-1, 0);
                    break;
                case SDLK_RIGHT:
                    game.movePlayerBall(1, 0);
                    break;
                default:
                    break;
                }
            }

            game.render();

            // Limit framerate
            capFramerate(startFrameTime);
        }
    }
    SDL_Quit();
    return 0;
}

void capFramerate(Uint32 startTick) {
    if ((1000 / FPS) > SDL_GetTicks() - startTick)
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTick));
}
