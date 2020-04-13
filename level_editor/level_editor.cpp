
#include <string>

#include "SDL2/SDL_ttf.h"

#include "core/globals.h"
#include "core/texture_loader.h"

#include "level_editor.h"

LevelEditor::LevelEditor() {
    EventDispatcher::subscribe(this, SDL_QUIT);
    EventDispatcher::subscribe(this, SDL_MOUSEBUTTONDOWN);
    EventDispatcher::subscribe(this, SDL_KEYDOWN);
    TTF_Init();
    mLabelFont = TTF_OpenFont("OpenSans-Bold.ttf", 16);
    if (!mLabelFont) {
        printf("Failed to load font\n");
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(-1);
    }
}

void LevelEditor::handleEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        saveLevelFile("level.yaml");
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        printf("Mouse down:: x: %d, y: %d\n", event.button.x, event.button.y);
        onClick(event.button.x, event.button.y, event.button.button);
    } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode sym = event.key.keysym.sym;
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

    Application::handleEvent(event);
}

void LevelEditor::start() {
    loadLevelFile("level.yaml");
    Application::start();
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

void LevelEditor::update() {
    // empty
}

void LevelEditor::render() {
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 206, 0, 255);
    mCamera.render(mRenderer, mLevelData);
    renderModeLabel();
    SDL_RenderPresent(mRenderer);
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
    // Text can only be put on a surface first and then converted to
    // texture.
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

    // Not very efficient since we create and destroy texture every frame
    // fix dis later.
    SDL_FreeSurface(labelSurface);
    SDL_DestroyTexture(labelTexture);
}

void LevelEditor::loadLevelFile(const char* path) { mLevelData.load(path); }
void LevelEditor::saveLevelFile(const char* path) { mLevelData.saveAs(path); }