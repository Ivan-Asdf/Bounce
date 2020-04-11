#include "core/terrain.h"

#include "player_ball.h"

class LiveTerrain : public Terrain {
public:
    void load(const char* path);
    void movePlayerBall(int x, int y);

private:
    PlayerBall* mPlayerBall = nullptr;
};