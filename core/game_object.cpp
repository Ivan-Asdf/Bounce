#include <stdio.h>

#include "globals.h"

#include "game_object.h"

GameObject::GameObject(Rect rect, TextureId textureId)
    : mRect(rect), mTextureId(textureId) {}

const Rect GameObject::getRect() const { return mRect; }
SDL_Texture* GameObject::getTexture() const {
    return TextureLoader::getTexture(mTextureId);
}

Tile::Tile(int x, int y, unsigned size)
    : GameObject(Rect(x, y, size, size), TEXTURE_BRICK) {}

Ball::Ball(int x, int y, unsigned size)
    : GameObject(Rect(x, y, size, size), TEXTURE_BALL) {}

Ball::Ball(const Ball& ball) : GameObject(ball.mRect, ball.mTextureId) {}
