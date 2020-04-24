#include <SDL2/SDL.h>

// temp
#include "game/player_ball.h"
#include "game_object.h"
#include "globals.h"

#include "camera.h"

Camera::Camera() : mRect(0, 0, 13 * TILE_SIZE, 8 * TILE_SIZE) {}

void Camera::render(SDL_Renderer* renderer, const Level& level) {
    for (const GameObject* object : level.getGameObjects()) {
        Rect rect = object->getRect();
        if (isColliding(rect, mRect)) {
            SDL_Rect sdlRect;
            sdlRect.x = rect.x;
            sdlRect.y = rect.y;
            absoluteToView(sdlRect.x, sdlRect.y);
            sdlRect.w = rect.w;
            sdlRect.h = rect.h;
            // printf("SDL_Rect> x: %d, y: %d, w %lu, h %lu\n", sdlRect.x,
            //       sdlRect.y, sdlRect.w, sdlRect.h);
            SDL_Rect srcrect{0, 0, 512, 512};
            SDL_RenderCopy(renderer, object->getTexture(), &srcrect, &sdlRect);
        }
    }
}

void Camera::absoluteToView(int& x, int& y) {
    x -= mRect.x;
    y -= mRect.y;
}
void Camera::viewToAbsolute(int& x, int& y) {
    x += mRect.x;
    y += mRect.y;
}
void Camera::move(int x, int y) {
    mRect.x += x * TILE_SIZE;
    mRect.y += y * TILE_SIZE;
}
void Camera::resize(unsigned w, unsigned h) {
    mRect.w = w;
    mRect.h = h;
}