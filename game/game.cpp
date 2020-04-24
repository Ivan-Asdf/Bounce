//#include <SDL2/SDL.h>
#include <assert.h>

#include "core/event_dispatcher.h"
#include "core/globals.h"

#include "collision_engine.h"

#include "game.h"

Game::Game() {}

void Game::start() {
    loadLevelFile("level.yaml");
    Application::start();
}

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

void Game::loadLevelFile(const char* path) {
    mLiveLevelData.load(path);
    mCollEngine = new CollisionEngine(&mLiveLevelData);
}