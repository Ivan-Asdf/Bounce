
#include "core/application.h"
#include "core/camera.h"

#include "live_camera.h"
#include "live_level.h"

class CollisionEngine;

class Game : public Application {
public:
    Game();

    void start();

private:
    void render();
    void update();
    void loadLevelFile(const char* path);

    LiveLevel mLiveLevelData;
    LiveCamera mCamera;
    CollisionEngine* mCollEngine;
};