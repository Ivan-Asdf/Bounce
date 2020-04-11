//#include <SDL2/SDL.h>

#include "game.h"

Game::Game(SDL_Renderer* renderer) : mRenderer(renderer) {}

// Reduce this duplication between Game and LevelEditor
void Game::render() {
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 206, 0, 255);
    mCamera.render(mRenderer, mTerrain);
    SDL_RenderPresent(mRenderer);
}

void Game::loadLevelFile(const char* path) { mTerrain.load(path); }

void Game::movePlayerBall(int x, int y) { mTerrain.movePlayerBall(x, y); }