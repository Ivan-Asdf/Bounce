#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#include <SDL2/SDL_ttf.h>

#include "core/globals.h"
#include "level_editor.h"

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
    if (!window || !renderer)
        printf("Failed to create window or renderer\n");

    LevelEditor levelEditor(renderer);
    levelEditor.loadLevelFile("level.yaml");

    TextureLoader::init(renderer);

    SDL_Event event;
    bool quit = false;
    bool recentMove = false;
    Uint32 startFrameTime;
    while (!quit) {
        startFrameTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                levelEditor.saveLevelFile("level_save.yaml");
                break;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    levelEditor.resizeCamera(event.window.data1,
                                             event.window.data2);
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                printf("Mouse down:: x: %d, y: %d\n", event.button.x,
                       event.button.y);
                levelEditor.onClick(event.button.x, event.button.y,
                                    event.button.button);
            } else if (event.type == SDL_KEYDOWN) {
                printf("KEYDOWN\n");
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (!recentMove)
                        levelEditor.moveCamera(0, -1);
                    recentMove = true;
                    break;
                case SDLK_DOWN:
                    if (!recentMove)
                        levelEditor.moveCamera(0, 1);
                    recentMove = true;
                    break;
                case SDLK_LEFT:
                    if (!recentMove)
                        levelEditor.moveCamera(-1, 0);
                    recentMove = true;
                    break;
                case SDLK_RIGHT:
                    if (!recentMove)
                        levelEditor.moveCamera(1, 0);
                    recentMove = true;
                    break;
                default:
                    levelEditor.onKeyDown(event.key.keysym.sym);
                    break;
                }

            } else if (event.type == SDL_KEYUP) {
                printf("KEYUP\n");
                recentMove = false;
            }
        }

        levelEditor.render();

        // Limit framerate
        capFramerate(startFrameTime);
    }

    SDL_Quit();
    return 0;
}

void capFramerate(Uint32 startTick) {
    if ((1000 / FPS) > SDL_GetTicks() - startTick)
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTick));
}
