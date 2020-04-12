
#include <string>

#include "SDL2/SDL_ttf.h"

#include "core/globals.h"
#include "core/texture_loader.h"

#include "level_editor.h"

LevelEditor::LevelEditor(SDL_Renderer* renderer) : mRenderer(renderer) {
    mLabelFont = TTF_OpenFont("OpenSans-Bold.ttf", 16);
    if (!mLabelFont) {
        printf("Failed to load font\n");
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }
}

void LevelEditor::onClick(int x, int y, int button) {
    if (button == SDL_BUTTON_LEFT) {
        mCamera.viewToAbsolute(x, y);
        for (; x % TILE_SIZE != 0; --x)
            ;
        for (; y % TILE_SIZE != 0; --y)
            ;

        GameObject* object = nullptr;
        if (mode != ERASE) {
            switch (mode) {
            case TILE:
                object = new Tile(x, y, TILE_SIZE);
                break;
            case BALL:
                object = new Ball(x, y, TILE_SIZE);
                break;
            default:
                printf("Should not be happening\n");
                break;
            }
            mLevelData.addObject(object);
        } else {
            mLevelData.removeObjectAt(x, y);
        }
    }
}

void LevelEditor::render() {
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 206, 0, 255);
    mCamera.render(mRenderer, mLevelData);
    renderModeLabel();
    SDL_RenderPresent(mRenderer);
}

void LevelEditor::moveCamera(int x, int y) { mCamera.move(x, y); }
void LevelEditor::resizeCamera(unsigned w, unsigned h) { mCamera.resize(w, h); }

void LevelEditor::onKeyDown(SDL_Keycode sym) {
    switch (sym) {
    case SDLK_e:
        mode = ERASE;
        break;

    case SDLK_t:
        mode = TILE;
        break;

    case SDLK_b:
        mode = BALL;
        break;
    }
}

void LevelEditor::renderModeLabel() {
    std::string labelText;
    switch (mode) {
    case ERASE:
        labelText = "ERASE";
        break;

    case TILE:
        labelText = "INSERT TILE";
        break;

    case BALL:
        labelText = "INSERT BALL";
        break;

    default:
        break;
    }

    if (!mLabelFont) {
        printf("No font loaded to render(this should not happen)\n");
        return;
    }

    SDL_Color color = {0, 0, 0, 255};
    // Text can only be put on a surface first and then converted to texture.
    SDL_Surface* labelSurface =
        TTF_RenderText_Solid(mLabelFont, labelText.c_str(), color);
    if (!labelSurface) {
        printf("Failed to create label surface\n");
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }

    SDL_Texture* labelTexture =
        SDL_CreateTextureFromSurface(mRenderer, labelSurface);
    if (!labelTexture) {
        printf("Failed to create label texture\n");
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }
    SDL_Rect labelRect;
    labelRect.x = 0;
    labelRect.y = 0;
    labelRect.w = 100;
    labelRect.h = 20;

    SDL_RenderCopy(mRenderer, labelTexture, NULL, &labelRect);

    // Not very efficient since we create and destroy texture every frame fix
    // dis later.
    SDL_FreeSurface(labelSurface);
    SDL_DestroyTexture(labelTexture);
}

void LevelEditor::loadLevelFile(const char* path) { mLevelData.load(path); }
void LevelEditor::saveLevelFile(const char* path) { mLevelData.saveAs(path); }