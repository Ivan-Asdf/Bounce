#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "geometry.h"
#include "texture_loader.h"

class GameObject {
public:
    GameObject(Rect rect, TextureId textureId);
    virtual const Rect getRect() const;
    virtual SDL_Texture* getTexture() const;

    friend class YAML::convert<std::vector<GameObject*>>;

protected:
    Rect mRect;
    TextureId mTextureId;
};

class Tile : public GameObject {
public:
    Tile(int x, int y, unsigned size);
};

class Ball : public GameObject {
public:
    Ball(int x, int y, unsigned size);

protected:
    Ball(const Ball& ball);
    // friend class YAML::convert<std::vector<GameObject*>>;
};