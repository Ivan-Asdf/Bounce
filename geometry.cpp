#include <stdio.h>

#include "geometry.h"

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

bool isColliding(int x, int y, Rect r) {
    return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
}