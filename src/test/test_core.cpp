#include <gtest/gtest.h>

#include <core/geometry.h>

TEST(geometry, Vector2D) {
    Vector2D v1(0, 0, 2, 2);
    EXPECT_NEAR(2.82842712475, v1.length(), 0.00000001);
    clampVector(v1, 1, 1);
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 1);

    Vector2D v2(0, 0, -2, -2);
    EXPECT_NEAR(2.82842712475, v2.length(), 0.00000001);
    clampVector(v2, 1, 1);
    EXPECT_EQ(v2.x, -1);
    EXPECT_EQ(v2.y, -1);

    Point p1(0, 0);
    Point p2(3.5, 5.0);
    Vector2D v3(p1, p2);
    EXPECT_DOUBLE_EQ(v3.x, p2.x);
    EXPECT_DOUBLE_EQ(v3.y, p2.y);
}

TEST(geometry, isColliding) {
    // Point and Rect overload
    Point p1(0, 2);
    Rect r1(0, 0, 2, 2);
    EXPECT_TRUE(isColliding(p1, r1));

    // Circle & Rect overload
    Circle c(0, 0, 3);
    Rect r2(4, 0, 3, 3);
    EXPECT_FALSE(isColliding(c, r2));

    Circle c1(0, 0, 3);
    Rect r3(3, 0, 3, 3);
    EXPECT_TRUE(isColliding(c1, r3));

    Circle c2(2, 2, 0.5);
    Rect r4(1, 1, 3, 3);
    EXPECT_TRUE(isColliding(c2, r4));
}