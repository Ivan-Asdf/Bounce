#include "core/globals.h"

#include "live_terrain.h"

const LevelData& LiveLevelData::getBase() const {
    return static_cast<const LevelData&>(*this);
}

const PlayerBall* const LiveLevelData::getPlayerBall() const {
    return mPlayerBall;
}

PlayerBall* const LiveLevelData::getPlayerBall() { return mPlayerBall; }

void LiveLevelData::load(const char* path) {
    LevelData::load(path);
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

void LiveLevelData::updatePlayer() { mPlayerBall->update(); }
