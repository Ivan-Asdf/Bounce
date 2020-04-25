#pragma once

struct Rect {
    Rect();
    Rect(int x, int y, unsigned int width, unsigned height);

    void print(const char* prefix = "") const;

    int x, y;
    unsigned int w, h;
};

bool isColliding(Rect r1, Rect r2);
bool isColliding(int x, int y, Rect r);

struct Circle {
    Circle(double x, double y, double r) : x(x), y(y), r(r) {}
    Circle(Rect rect);
    // Circle(double x, double y, double r);
    const Rect rect() const;

    double x;
    double y;
    double r;
};

class Vector2D;

struct Point {
    Point(double x, double y);
    Point(Point p, Vector2D v);
    double x;
    double y;
};

bool isColliding(Point p, Rect r);

struct Vector2D {
    Vector2D(double x1, double y1, double x2, double y2);
    Vector2D(Point p1, Point p2);

    double length();

    double x;
    double y;
};

// Limits vector absolute value to xMax and yMax
void clampVector(Vector2D& v, double xMax, double yMax);

bool isColliding(Circle c, Rect r);