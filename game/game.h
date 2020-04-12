
#include "core/camera.h"

#include "live_camera.h"
#include "live_terrain.h"

class CollisionEngine;

class Game {
public:
    Game(SDL_Renderer* renderer);

    void render();
    void update();
    void handleKeyPress(SDL_Keycode code);
    void loadLevelFile(const char* path);

private:
    LiveLevelData mLiveLevelData;
    LiveCamera mCamera;
    CollisionEngine* mCollEngine;
    SDL_Renderer* mRenderer;
};