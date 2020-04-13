#include <stdio.h>

#include <SDL2/SDL.h>
#undef main // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#include <SDL2/SDL_ttf.h>

#include "core/globals.h"
#include "core/texture_loader.h"

#include "game.h"

int main() {
    Game game;
    game.start();
    return 0;
}