#pragma once

#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum TextureId { TEXTURE_BRICK, TEXTURE_BALL, TEXTURE_GRID };

class TextureLoader {
public:
    static void init(SDL_Renderer* renderer);
    static SDL_Texture* getTexture(TextureId id);

private:
    TextureLoader(SDL_Renderer* renderer);
    SDL_Texture* getTexturePrivate(TextureId id) const;
    void loadTexture(SDL_Renderer* renderer, TextureId id, const char* path);

private:
    static TextureLoader* mInstance;

    std::map<TextureId, SDL_Texture*> mTextures;
};