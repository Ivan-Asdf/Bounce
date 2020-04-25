#include "core/globals.h"

#include "level_camera.h"

LevelCamera::LevelCamera() {
    EventDispatcher::subscribe(this, SDL_WINDOWEVENT);
    EventDispatcher::subscribe(this, SDL_KEYDOWN);
}

void LevelCamera::handleEvent(SDL_Event event) {
    if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            resize(event.window.data1, event.window.data2);
        }
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            move(0, -1);
            break;
        case SDLK_DOWN:
            move(0, 1);
            break;
        case SDLK_LEFT:
            move(-1, 0);
            break;
        case SDLK_RIGHT:
            move(1, 0);
            break;
        default:
            break;
        }
    } else {
        // bad
    }
}

void LevelCamera::render(SDL_Renderer* renderer, const Level& level) {
    // Render grid
    for (int iY = 0; iY < mRect.h; iY += TILE_SIZE) {
        for (int iX = 0; iX < mRect.w; iX += TILE_SIZE) {
            SDL_Rect sdlRect;
            sdlRect.x = iX;
            sdlRect.y = iY;
            sdlRect.w = TILE_SIZE;
            sdlRect.h = TILE_SIZE;
            SDL_Rect srcrect{0, 0, 64, 64};
            SDL_RenderCopy(renderer, TextureLoader::getTexture(TEXTURE_GRID),
                           &srcrect, &sdlRect);
        }
    }
    Camera::render(renderer, level);
}