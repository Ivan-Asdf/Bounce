#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>

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
    return x >= r.x && x <= r.x + r.w - 1 && y >= r.y && y <= r.y + r.h - 1;
}

enum CollisionDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct CollisionData {
    // Direction from first object perspective
    CollisionDirection dir;
    // How much the objects overlap which each other.
    int delta;
};

Circle::Circle(Rect rect) {
    assert(("Rect not a square", rect.h == rect.h));
    r = rect.w / 2;
    x = rect.x + r;
    y = rect.y + r;
}
// Circle::Circle(double x, double y, double r) : x(x), y(y), mR(r) {}

// Round this up later
const Rect Circle::rect() const { return Rect(x - r, y - r, 2 * r, 2 * r); }

class Vector2D;
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(Point p, Vector2D v) : x(p.x + v.x), y(p.y + v.y) {}

bool isColliding(Point p, Rect r) {
    return p.x >= r.x && p.y >= r.y && p.x <= r.x + r.w && p.y <= r.y + r.h;
}

// Vector from x1,y1 to x2,y2
Vector2D::Vector2D(double x1, double y1, double x2, double y2)
    : x(x2 - x1), y(y2 - y1) {}

Vector2D::Vector2D(Point p1, Point p2) : Vector2D(p1.x, p1.y, p2.x, p2.y) {}

double Vector2D::length() { return sqrt(pow(x, 2) + pow(y, 2)); }

// Limit vector absolute values to xMax and yMax. xMax & yMax must be positive
void clampVector(Vector2D& v, double xMax, double yMax) {
    assert(xMax >= 0 && yMax >= 0);
    if (v.x > 0)
        v.x = std::min(v.x, xMax);
    else
        v.x = std::max(v.x, -xMax);

    if (v.y > 0)
        v.y = std::min(v.y, yMax);
    else
        v.y = std::max(v.y, -yMax);
}

bool isColliding(Circle c, Rect r) {
    Point centerCircle(c.x, c.y);
    // If circle center is inside rect
    if (isColliding(centerCircle, r))
        return true;
    Point centerRect(r.x + r.w / 2.0, r.y + r.h / 2.0);
    // Distance between center of rect to center of circle
    Vector2D centerToCenter(centerRect, centerCircle);
    // This will make vector from center of rect to its edge point, closest to
    // circle.
    clampVector(centerToCenter, r.w / 2.0, r.h / 2.0);
    Point rectEdge(centerRect, centerToCenter);
    Vector2D edgeToCircleCenter(rectEdge, centerCircle);
    if (edgeToCircleCenter.length() <= c.r)
        return true;
    else
        return false;
};