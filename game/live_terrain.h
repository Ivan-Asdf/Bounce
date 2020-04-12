#include "core/terrain.h"

#include "player_ball.h"

struct Speed {
    double x;
    double y;
};

// Adds the PlayerBall member
// Collision engine should have read/write access to PlayerBall
// LiveCamera should have read access to PlayerBall
class LiveLevelData : public LevelData {
public:
    // Read only for LiveCamera Camera::render() method
    const LevelData& getBase() const;
    // Read only for LiveCamera render() method
    const PlayerBall* const getPlayerBall() const;
    // Non-read only for Collision engine
    PlayerBall* const getPlayerBall();

    void load(const char* path);

    // Used by Game and CollisionEngine
    // void changePlayerSpeed(double deltaX, double deltaY);
    // Speed getPlayerSpeed();
    // void setPlayerSpeed(double x, double y);

    void updatePlayer();

private:
    PlayerBall* mPlayerBall = nullptr;
};