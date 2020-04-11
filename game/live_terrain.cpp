#include "live_terrain.h"

void LiveTerrain::load(const char* path) {
    Terrain::load(path);
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

void LiveTerrain::movePlayerBall(int x, int y) {
    if (mPlayerBall)
        mPlayerBall->move(x, y);
}