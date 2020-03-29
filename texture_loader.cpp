
#include "texture_loader.h"

TextureLoader* TextureLoader::mInstance = nullptr;

void TextureLoader::init(SDL_Renderer* renderer) {
    if (!mInstance)
        mInstance = new TextureLoader(renderer);
    else
        printf("TextureLoader already initialized");
}

SDL_Texture* TextureLoader::getTexture(TextureId id) {
    if (mInstance)
        return mInstance->getTexturePrivate(id);
    else {
        printf("TextureLoader not initialized");
        return NULL;
    }
}

TextureLoader::TextureLoader(SDL_Renderer* renderer) {
    loadTexture(renderer, TEXTURE_BRICK, "brick.png");
    loadTexture(renderer, TEXTURE_BALL, "ball.png");
    loadTexture(renderer, TEXTURE_GRID, "grid.png");
}

SDL_Texture* TextureLoader::getTexturePrivate(TextureId id) const {
    return mTextures.at(id);
}

void TextureLoader::loadTexture(SDL_Renderer* renderer, TextureId id,
                                const char* path) {
    // Check if texture is already loaded
    if (mTextures.find(id) != mTextures.end())
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
    mTextures.insert(p);
}