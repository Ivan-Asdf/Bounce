
#include <string>

#include "SDL2/SDL_ttf.h"

#include "level_editor.h"

Camera::Camera() : mRect(0, 0, 13 * TILE_SIZE, 8 * TILE_SIZE) {}

void Camera::render(SDL_Renderer* renderer, const Terrain& terrain) {
    // Render grid
    for (int iY = 0; iY < mRect.h; iY += TILE_SIZE) {
        for (int iX = 0; iX < mRect.w; iX += TILE_SIZE) {
            SDL_Rect sdlRect;
            sdlRect.x = iX;
            sdlRect.y = iY;
            sdlRect.w = TILE_SIZE;
            sdlRect.h = TILE_SIZE;
            SDL_Rect srcrect{0, 0, 64, 64};
            SDL_RenderCopy(renderer, gTextures[TEXTURE_GRID], &srcrect,
                           &sdlRect);
        }
    }
    // SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    for (const GameObject* object : terrain.objects) {
        Rect rect = object->getRect();
        if (isColliding(rect, mRect)) {
            SDL_Rect sdlRect;
            sdlRect.x = rect.x;
            sdlRect.y = rect.y;
            absoluteToView(sdlRect.x, sdlRect.y);
            sdlRect.w = rect.w;
            sdlRect.h = rect.h;
            // printf("SDL_Rect> x: %d, y: %d, w %lu, h %lu\n", sdlRect.x,
            //       sdlRect.y, sdlRect.w, sdlRect.h);
            SDL_Rect srcrect{0, 0, 512, 512};
            SDL_RenderCopy(renderer, object->getTexture(), &srcrect, &sdlRect);
            // SDL_RenderFillRect(renderer, &sdlRect);
        }
    }
}

void Camera::absoluteToView(int& x, int& y) {
    x -= mRect.x;
    y -= mRect.y;
}
void Camera::viewToAbsolute(int& x, int& y) {
    x += mRect.x;
    y += mRect.y;
}
void Camera::move(int x, int y) {
    mRect.x += x * TILE_SIZE;
    mRect.y += y * TILE_SIZE;
}
void Camera::resize(unsigned w, unsigned h) {
    mRect.w = w;
    mRect.h = h;
}

LevelEditor::LevelEditor(SDL_Renderer* renderer) : mRenderer(renderer) {}

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
            mTerrain.addObject(object);
        } else {
            // Erase logic
        }
    }
}

void LevelEditor::render() {
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 206, 0, 255);
    mCamera.render(mRenderer, mTerrain);
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

    TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 16);

    if (!font) {
        printf("Failed to laod font\n");
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    SDL_Color color = {0, 0, 0};
    // Text can only be put on a surface first and then converted to texture.
    SDL_Surface* labelSurface =
        TTF_RenderText_Solid(font, labelText.c_str(), color);

    SDL_Texture* labelTexture =
        SDL_CreateTextureFromSurface(mRenderer, labelSurface);
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