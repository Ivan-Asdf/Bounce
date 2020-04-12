#include "core/game_object.h"

class LiveLevelData;

class PlayerBall : public Ball {
public:
    PlayerBall(Ball* ball);
    void update();
    void handleKeyPress(SDL_Keycode sym);

    friend class LiveLevelData;
    friend class CollisionEngine;

private:
    double mXSpeed = 0;
    double mYSpeed = 0;
    bool mIsOnFloor = false;
};