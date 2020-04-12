//#include <SDL2/SDL.h>

#include "collision_engine.h"

#include "game.h"

Game::Game(SDL_Renderer* renderer) : mRenderer(renderer) {}

// Reduce this duplication between Game and LevelEditor
void Game::render() {
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 206, 0, 255);
    mCamera.render(mRenderer, mLiveLevelData);
    SDL_RenderPresent(mRenderer);
}

void Game::update() {
    if (mCollEngine)
        mCollEngine->update();
    else
        puts("COLLION ENGINE NOT INITIALIZED");
}

void Game::handleKeyPress(SDL_Keycode code) {
    mLiveLevelData.getPlayerBall()->handleKeyPress(code);
}

void Game::loadLevelFile(const char* path) {
    mLiveLevelData.load(path);
    mCollEngine = new CollisionEngine(&mLiveLevelData);
}