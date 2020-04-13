#pragma once

class LiveLevel;

class CollisionEngine {
public:
    CollisionEngine(LiveLevel* liveLevelData);
    void update();
    // void changePlayerSpeed(int x, int y);
    // bool isPlayerBallColliding();
private:
    LiveLevel* const mLiveLevelData;
};