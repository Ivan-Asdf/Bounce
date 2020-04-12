#include "core/geometry.h"
#include "core/globals.h"

#include "live_terrain.h"

#include "collision_engine.h"

#define GRAVITY 10.0

CollisionEngine::CollisionEngine(LiveLevelData* liveLevelData)
    : mLiveLevelData(liveLevelData) {}

void CollisionEngine::update() {
    puts("Emter");
    mLiveLevelData->updatePlayer();
    PlayerBall* const playerBall = mLiveLevelData->getPlayerBall();
    bool isOnFloor = false;
    for (GameObject* gameObject : mLiveLevelData->getGameObjects()) {
        if (gameObject != playerBall) {
            if (isColliding(playerBall->getRect(), gameObject->getRect())) {
                isOnFloor = true;
                break;
            }
        }
    }

    if (isOnFloor && !playerBall->mIsOnFloor) {
        playerBall->mYSpeed = 0.0;
        playerBall->mIsOnFloor = true;
    } else if (!isOnFloor) {
        playerBall->mIsOnFloor = false;
        playerBall->mYSpeed += GRAVITY;
        puts("Reducing speed");
    }
}

// bool CollsionEngine::isPlayerBallColliding() {
//     for (int i = 0; i < mObjects.size(); ++i) {
//         if (mObjects[i] != mPlayerBall)
//             if (isColliding(mPlayerBall->getRect(), mObjects[i]->getRect()))
//             {
//                 return true;
//             }
//     }
//     return false;
// }