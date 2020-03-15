#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>

#include "level_editor.h"

#define FPS 200

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
    FPSmanager m;
    SDL_initFramerate(&m);
    SDL_setFramerate(&m, 60);
    bool quit = false;
    bool recentMove = false;
    while (!quit) {
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
        SDL_framerateDelay(&m);
        // printf("FPS: %d\n", SDL_getFramerate(&m));
    }

    SDL_Quit();
}
