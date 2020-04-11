#include "player_ball.h"

PlayerBall::PlayerBall(Ball* ball) : Ball(*ball) {}

void PlayerBall::move(int x, int y) {
    mRect.x += x;
    mRect.y += y;
}