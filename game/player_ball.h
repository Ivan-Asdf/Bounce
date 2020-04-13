#pragma once
#include "core/event_dispatcher.h"
#include "core/game_object.h"

class LiveLevel;

class PlayerBall : public Ball, public EventHandler {
public:
    PlayerBall(Ball* ball);
    void update();
    void handleEvent(SDL_Event event);

    friend class LiveLevel;
    friend class CollisionEngine;

private:
    double mXSpeed = 0;
    double mYSpeed = 0;
    bool mIsOnFloor = false;
};