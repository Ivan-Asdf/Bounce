#pragma once

class LiveLevel;
class PlayerBall;

class CollisionEngine {
public:
    CollisionEngine(LiveLevel* liveLevelData);
    void update();
    // void changePlayerSpeed(int x, int y);
private:
    bool isPlayerBallCollidingWithFloor(PlayerBall* playerBall);

    LiveLevel* const mLiveLevelData;
};