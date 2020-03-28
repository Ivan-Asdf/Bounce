#include <stdio.h>

#include <SDL2/SDL_image.h>

#include "game_object.h"

std::map<TextureId, SDL_Texture*> gTextures;

Rect::Rect(){};
Rect::Rect(int x, int y, unsigned int width, unsigned height)
    : x(x), y(y), w(width), h(height) {}

void Rect::print(const char* prefix) const {
    printf("%s Rect:: x: %d, y: %d, w: %lu, h: %lu\n", prefix, x, y, w, h);
}

bool isColliding(Rect r1, Rect r2) {
    // Which side of first rectangle(r1) is positioned how as to which side of
    // second rectangle(r2) LeftLeftOfRight = Left side of r1 is to the left of
    // right side of r2
    bool leftLeftOfRight = r1.x < (r2.x + (int)r2.w);
    bool rightRightOfLeft = (r1.x + (int)r1.w) > r2.x;
    bool topAboveBottom = r1.y < (r2.y + (int)r2.h);
    bool bottomBelowTop = (r1.y + (int)r1.h) > r2.y;
    // printf("l: %d, r: %d, t: %d, b: %d\n", leftLeftOfRight, rightRightOfLeft,
    // topAboveBottom,
    //       bottomBelowTop);
    // printf("r1y: %d, r1h: %d, r2y: %d\n", r1.y, r1.h, r2.y);
    if (leftLeftOfRight && rightRightOfLeft && topAboveBottom && bottomBelowTop)
        return true;
    else
        return false;
}

void loadTexture(SDL_Renderer* renderer, TextureId id, const char* path) {
    // Check if texture is already loaded
    if (gTextures.find(id) != gTextures.end())
        return;

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path); // Never deleted fix dis
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path,
               IMG_GetError());
    } else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(
            renderer, loadedSurface); // Never deleted fix dis
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path,
                   SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    std::pair<TextureId, SDL_Texture*> p(id, newTexture);
    gTextures.insert(p);
}

GameObject::GameObject(Rect rect, TextureId textureId)
    : mRect(rect), mTextureId(textureId) {}

const Rect GameObject::getRect() const { return mRect; }
SDL_Texture* GameObject::getTexture() const { return gTextures[mTextureId]; }

Tile::Tile(int x, int y, unsigned size)
    : GameObject(Rect(x, y, size, size), TEXTURE_BRICK) {}

Ball::Ball(int x, int y, unsigned size)
    : GameObject(Rect(x, y, size, size), TEXTURE_BALL) {}

void Terrain::addObject(GameObject* object) { objects.push_back(object); }
