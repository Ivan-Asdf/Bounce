#include "core/globals.h"

#include "live_level.h"

const Level& LiveLevel::getBase() const {
    return static_cast<const Level&>(*this);
}

const PlayerBall* const LiveLevel::getPlayerBall() const { return mPlayerBall; }

PlayerBall* const LiveLevel::getPlayerBall() { return mPlayerBall; }

void LiveLevel::load(const char* path) {
    Level::load(path);
    for (int i = 0; i < mObjects.size(); ++i) {
        Ball* ball = dynamic_cast<Ball*>(mObjects[i]);
        if (ball) {
            PlayerBall* playerBall = new PlayerBall(ball);
            // Delete Ball?

            mObjects.erase(mObjects.begin() + i);
            mObjects.push_back(playerBall);
            mPlayerBall = playerBall;
            break;
        } else {
            puts("NOT BALL");
        }
    }
}

// void LiveLevelData::changePlayerSpeed(double deltaX, double deltaY) {
//     mPlayerBall->mXSpeed += deltaX;
//     mPlayerBall->mYSpeed += deltaY;
// }

// Speed LiveLevelData::getPlayerSpeed() {
//     Speed speed;
//     speed.x = mPlayerBall->mXSpeed;
//     speed.y = mPlayerBall->mYSpeed;
//     return speed;
// }

// void LiveLevelData::setPlayerSpeed(double x, double y) {
//     mPlayerBall->mXSpeed = x;
//     mPlayerBall->mYSpeed = y;
// }

void LiveLevel::updatePlayer() { mPlayerBall->update(); }
