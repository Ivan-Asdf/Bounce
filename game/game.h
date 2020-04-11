
#include "core/camera.h"

#include "live_terrain.h"

class Game {
public:
    Game(SDL_Renderer* renderer);

    void render();
    void loadLevelFile(const char* path);
    void movePlayerBall(int x, int y);

private:
    LiveTerrain mTerrain;
    Camera mCamera;
    SDL_Renderer* mRenderer;
};