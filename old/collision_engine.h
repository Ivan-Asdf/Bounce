#pragma once
#include <cmath>
#include <vector>

class Collision {
public:
    Collision(Fighter* f1, Fighter* f2);

    bool operator==(Collision otherCollision);

    Fighter* mF1;
    Fighter* mF2;
};

class CollisionEngine {
public:
    void addCollisionObject(Fighter* f);
    void checkCollision();

private:
    void addCollision(Fighter* f1, Fighter* f2);
    void dispatchCollisions();
    std::vector<Fighter*> mCollisionObjects;
    std::vector<Collision> mCollisions;
};