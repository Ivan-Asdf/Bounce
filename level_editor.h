
#include <vector>

#include <SDL2/SDL.h>

#define TILE_SIZE 64

struct Rect {
    Rect(){};
    Rect(int x, int y, unsigned int width, unsigned height)
        : x(x), y(y), w(width), h(height) {}

    void print(const char* prefix) const {
        printf("%s Rect:: x: %d, y: %d, w: %lu, h: %lu\n", prefix, x, y, w, h);
    }

    int x, y;
    unsigned int w, h;
};

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

class Terrain {
public:
    void addObject(const Rect& rect) { objects.push_back(rect); }
    std::vector<Rect> objects;
};

class Camera {
public:
    Camera() : mRect(0, 0, 13 * TILE_SIZE, 8 * TILE_SIZE) {}
    void render(SDL_Renderer* renderer, const Terrain& terrain) {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        for (const Rect r : terrain.objects) {
            if (isColliding(r, mRect)) {
                SDL_Rect sdlRect;
                sdlRect.x = r.x;
                sdlRect.y = r.y;
                absoluteToView(sdlRect.x, sdlRect.y);
                sdlRect.w = r.w;
                sdlRect.h = r.h;
                // printf("SDL_Rect> x: %d, y: %d, w %lu, h %lu\n", sdlRect.x,
                //       sdlRect.y, sdlRect.w, sdlRect.h);
                SDL_RenderFillRect(renderer, &sdlRect);
            }
        }
    }

    void absoluteToView(int& x, int& y) {
        x -= mRect.x;
        y -= mRect.y;
    }
    void viewToAbsolute(int& x, int& y) {
        x += mRect.x;
        y += mRect.y;
    }
    void move(int X, int Y) {
        mRect.x += X * TILE_SIZE;
        mRect.y += Y * TILE_SIZE;
    }

private:
    Rect mRect;
};

class LevelEditor {
public:
    void onClick(int x, int y) {
        mCamera.viewToAbsolute(x, y);
        Rect rect;
        rect.w = TILE_SIZE;
        rect.h = TILE_SIZE;
        for (; x % TILE_SIZE != 0; --x)
            ;
        for (; y % TILE_SIZE != 0; --y)
            ;
        rect.x = x;
        rect.y = y;
        mTerrain.addObject(rect);
    }

    void render() {
        SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
        SDL_RenderClear(mRenderer);
        mCamera.render(mRenderer, mTerrain);
        SDL_RenderPresent(mRenderer);
    }
    void setRenderer(SDL_Renderer* r) { mRenderer = r; }
    void moveCamera(int x, int y) { mCamera.move(x, y); }

private:
    Terrain mTerrain;
    Camera mCamera;
    SDL_Renderer* mRenderer;
};