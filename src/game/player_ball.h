#pragma once
#include "core/event_dispatcher.h"
#include "core/game_object.h"
#include "core/geometry.h"

class LiveLevel;

class PlayerBall : public Ball, private EventHandler {
public:
    PlayerBall(Ball* ball);
    void update();
    const Rect getRect() const override;
    void handleEvent(SDL_Event event) override;

    friend class CollisionEngine;

private:
    Circle mCircle;

    double mXSpeed = 0;
    double mYSpeed = 0;
    bool mRecentlyOnFloor = false;
};