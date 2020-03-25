#include <stdio.h>

#include <SDL2/SDL.h>
#undef main //https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc

#include "level_editor.h"

#define FPS 60

void capFramerate(Uint32 startTick);

int main() {
    int rc = SDL_Init(SDL_INIT_VIDEO);
    if (rc)
        printf("Failed to initialize SDL2. Error: %d\n", rc);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    rc = SDL_CreateWindowAndRenderer(13 * TILE_SIZE, 8 * TILE_SIZE,
                                     SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (rc)
        printf("Failed to create window\n");

    Terrain terrain;
    LevelEditor levelEditor;
    Camera camera;
    levelEditor.setTerrain(&terrain);
    camera.setTerrain(&terrain);

    SDL_Event event;
    bool quit = false;
    bool recentMove = false;
    Uint32 startFrameTime;
    while (!quit) {
        startFrameTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                printf("Mouse down:: x: %d, y: %d\n", event.button.x,
                       event.button.y);
                levelEditor.onClick(event.button.x, event.button.y);
            } else if (event.type == SDL_KEYDOWN) {
                printf("KEYDOWN\n");
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (!recentMove)
                        camera.move(0, -1);
                    recentMove = true;
                    break;
                case SDLK_DOWN:
                    if (!recentMove)
                        camera.move(0, 1);
                    recentMove = true;
                    break;
                case SDLK_LEFT:
                    if (!recentMove)
                        camera.move(-1, 0);
                    recentMove = true;
                    break;
                case SDLK_RIGHT:
                    if (!recentMove) {
                        camera.move(1, 0);
                        printf("Move Right\n");
                    }
                    recentMove = true;
                    break;
                }
            } else if (event.type == SDL_KEYUP) {
                printf("KEYUP\n");
                recentMove = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);
        camera.render(renderer);
        SDL_RenderPresent(renderer);

        // Limit framerate
        capFramerate(startFrameTime);
    }

    SDL_Quit();
    return 0;
}

void capFramerate(Uint32 startTick)
{
    if ((1000 / FPS) > SDL_GetTicks() - startTick)
        SDL_Delay( 1000 / FPS - (SDL_GetTicks() - startTick));
}
