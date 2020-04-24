#include <SDL2/SDL.h>

#include "core/event_dispatcher.h"
#include "core/globals.h"

#include "player_ball.h"

PlayerBall::PlayerBall(Ball* ball) : Ball(*ball), mCircle(ball->getRect()) {
    EventDispatcher::subscribe(this, SDL_KEYDOWN);
}

void PlayerBall::update() {
    if (mXSpeed > 0) {
        if (abs(mXSpeed) < 20 / FPS)
            mXSpeed = 0;
        else
            mXSpeed -= 20 / FPS;
    } else if (mXSpeed < 0) {
        if (abs(mXSpeed) > -20 / FPS)
            mXSpeed = 0;
        else
            mXSpeed += 20 / FPS;
    }
    mCircle.x += mXSpeed / FPS;
    mCircle.y += mYSpeed / FPS;
    // printf("x: %d, y: %d\n", mRect.x, mRect.y);
}

const Rect PlayerBall::getRect() const { return mCircle.rect(); }

void PlayerBall::handleEvent(SDL_Event event) {
    // Only subscribed to SDL_KEYDOWN so we assume its that
    SDL_Keycode sym = event.key.keysym.sym;
    switch (sym) {
    case SDLK_UP:
        if (mRecentlyOnFloor) {
            mYSpeed -= 200.0;
            puts("Speed set");
        }
        break;
    case SDLK_DOWN:
        // game.changePlayerSpeed(0, 20);
        break;
    case SDLK_LEFT:
        mXSpeed -= 70;
        if (abs(mXSpeed) > BALL_MAX_SPEED)
            mXSpeed = BALL_MAX_SPEED;
        break;
    case SDLK_RIGHT:
        mXSpeed += 70;
        if (abs(mXSpeed) > BALL_MAX_SPEED)
            mXSpeed = BALL_MAX_SPEED;
        break;
    default:
        break;
    }
    printf("Ball speed %lf %d\n", mYSpeed, mRecentlyOnFloor);
}