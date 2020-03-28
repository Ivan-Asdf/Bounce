#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <vector>

enum TextureId { TEXTURE_BRICK, TEXTURE_BALL, TEXTURE_GRID };
extern std::map<TextureId, SDL_Texture*> gTextures;

struct Rect {
    Rect();
    Rect(int x, int y, unsigned int width, unsigned height);

    void print(const char* prefix) const;

    int x, y;
    unsigned int w, h;
};

bool isColliding(Rect r1, Rect r2);
void loadTexture(SDL_Renderer* renderer, TextureId id, const char* path);

class GameObject {
public:
    GameObject(Rect rect, TextureId textureId);
    virtual const Rect getRect() const;
    virtual SDL_Texture* getTexture() const;

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
};

class Terrain {
public:
    void addObject(GameObject* object);
    std::vector<GameObject*> objects;
};