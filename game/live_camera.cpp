#include "live_terrain.h"

#include "live_camera.h"

void LiveCamera::render(SDL_Renderer* renderer,
                        const LiveLevelData& liveLevelData) {
    const PlayerBall* const playerBall = liveLevelData.getPlayerBall();
    // Center camera on playerBall
    mRect.x = playerBall->getRect().x - mRect.w / 2;
    mRect.y = playerBall->getRect().y - mRect.h / 2;
    Camera::render(renderer, liveLevelData.getBase());
}