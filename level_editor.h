
#include <vector>

#include <SDL2/SDL.h>

#define TILE_SIZE 64

struct Rect {
    Rect(){};
    Rect(int x, int y, unsigned int width, unsigned height)
        : x(x), y(y), w(width), h(height) {}
    int x, y;
    unsigned int w, h;
    void print(const char* prefix) const {
        printf("%s Rect:: x: %d, y: %d, w: %lu, h: %lu\n", prefix, x, y, w, h);
    }
};

// test dis
bool isColliding(Rect r1, Rect r2) {
    bool leftSide = r1.x < (r2.x + r2.w);
    bool rightSize = (r1.x + r1.w) > r2.x;
    bool topSize = r1.y < (r2.y + r2.h);
    bool botSize = (r1.y + r1.h) > r2.y;
    printf("l: %d, r: %d, t: %d, b: %d\n", leftSide, rightSize, topSize,
           botSize);
    printf("r1y: %d, r1h: %d, r2y: %d\n", r1.y, r1.h, r2.y);
    if (leftSide && rightSize && topSize && botSize)
        return true;
    else
        return false;
}

class Terrain {
public:
    void addObject(const Rect& rect) {
        rect.print("Terrain>");
        objects.push_back(rect);
    }
    std::vector<Rect> objects;
};

class Camera {
public:
    Camera() : m_rect(0, 0, 13 * TILE_SIZE, 8 * TILE_SIZE) {}
    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        for (Rect r : m_terrain->objects) {
            r.print("Real rect>");
            m_rect.print("Camera>");
            if (isColliding(r, m_rect)) {
                SDL_Rect sdlRect;
                sdlRect.x = r.x - m_rect.x;
                sdlRect.y = r.y - m_rect.y;
                sdlRect.w = r.w;
                sdlRect.h = r.h;
                printf("SDL_Rect> x: %d, y: %d, w %lu, h %lu\n", sdlRect.x,
                       sdlRect.y, sdlRect.w, sdlRect.h);
                SDL_RenderFillRect(renderer, &sdlRect);
            }
        }
    }

    void setTerrain(Terrain* t) { m_terrain = t; }
    void move(int X, int Y) {
        m_rect.x += X * TILE_SIZE;
        m_rect.y += Y * TILE_SIZE;
    }

private:
    Rect m_rect;
    Terrain* m_terrain;
};

class LevelEditor {
public:
    void onClick(int x, int y) {
        Rect rect;
        rect.w = gridBlockSize;
        rect.h = gridBlockSize;
        // Terrible on so many levels.. fix later
        for (; x % gridBlockSize != 0; --x)
            ;
        for (; y % gridBlockSize != 0; --y)
            ;
        rect.x = x;
        rect.y = y;
        m_terrain->addObject(rect);
    }

    void setTerrain(Terrain* t) { m_terrain = t; }

private:
    Terrain* m_terrain;
    unsigned int gridBlockSize = TILE_SIZE;
};