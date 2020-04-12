#pragma once

class LiveLevelData;

class CollisionEngine {
public:
    CollisionEngine(LiveLevelData* liveLevelData);
    void update();
    // void changePlayerSpeed(int x, int y);
    // bool isPlayerBallColliding();
private:
    LiveLevelData* const mLiveLevelData;
};