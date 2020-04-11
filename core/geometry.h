#pragma once

struct Rect {
    Rect();
    Rect(int x, int y, unsigned int width, unsigned height);

    void print(const char* prefix) const;

    int x, y;
    unsigned int w, h;
};

bool isColliding(Rect r1, Rect r2);
bool isColliding(int x, int y, Rect r);