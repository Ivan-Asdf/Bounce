#include "core/geometry.h"
#include "core/globals.h"

#include "live_level.h"
#include "player_ball.h"

#include "collision_engine.h"

#define GRAVITY 10.0

CollisionEngine::CollisionEngine(LiveLevel* liveLevelData)
    : mLiveLevelData(liveLevelData) {}

void CollisionEngine::update() {
    mLiveLevelData->updatePlayer();
    PlayerBall* const playerBall = mLiveLevelData->getPlayerBall();
    bool isOnFloor = false;
    isOnFloor = isPlayerBallCollidingWithFloor(playerBall);

    // printf("isOnFloor: %d, recentlyOnFloor: %d\n", isOnFloor,
    //    playerBall->mRecentlyOnFloor);
    if (isOnFloor && !playerBall->mRecentlyOnFloor) {
        // puts("hit floor");
        playerBall->mRecentlyOnFloor = true;
        playerBall->mYSpeed = 0.0;
    } else if (!isOnFloor) {
        playerBall->mRecentlyOnFloor = false;
        playerBall->mYSpeed += GRAVITY;
    }
}

bool CollisionEngine::isPlayerBallCollidingWithFloor(PlayerBall* playerBall) {
    for (GameObject* gameObject : mLiveLevelData->getGameObjects()) {
        if (gameObject != playerBall) {
            if (isColliding(playerBall->getRect(), gameObject->getRect())) {
                return true;
                break;
            }
        }
    }
    return false;
}