#include <SDL2/SDL.h>

#include "core/event_dispatcher.h"
#include "core/globals.h"

#include "player_ball.h"

PlayerBall::PlayerBall(Ball* ball) : Ball(*ball) {
    EventDispatcher::subscribe(this, SDL_KEYDOWN);
}

void PlayerBall::update() {
    mRect.x += mXSpeed / FPS;
    mRect.y += mYSpeed / FPS;
    // printf("x: %d, y: %d\n", mRect.x, mRect.y);
}

void PlayerBall::handleEvent(SDL_Event event) {
    // Only subscribed to SDL_KEYDOWN so we assume its that
    SDL_Keycode sym = event.key.keysym.sym;
    switch (sym) {
    case SDLK_UP:
        if (mIsOnFloor) {
            mYSpeed -= 200.0;
            puts("Speed set");
        }
        break;
    case SDLK_DOWN:
        // game.changePlayerSpeed(0, 20);
        break;
    case SDLK_LEFT:
        // game.changePlayerSpeed(-20, 0);
        break;
    case SDLK_RIGHT:
        // game.changePlayerSpeed(20, 0);
        break;
    default:
        break;
    }
    printf("Ball speed %lf %d\n", mYSpeed, mIsOnFloor);
}