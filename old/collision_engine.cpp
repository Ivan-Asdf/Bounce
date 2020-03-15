#include "collision_engine.h"

Collision::Collision(Fighter* f1, Fighter* f2) : mF1(f1), mF2(f2) {}

bool Collision::operator==(Collision otherCollision) {
    if (mF1 == otherCollision.mF1 && mF2 == otherCollision.mF2 ||
        mF2 == otherCollision.mF1 && mF1 == otherCollision.mF2)
        return true;
    else
        return false;
}

void CollisionEngine::addCollisionObject(Fighter* f) {
    mCollisionObjects.push_back(f);
}
void CollisionEngine::checkCollision() {
    for (int i = 0; i < mCollisionObjects.size(); ++i)
        for (int j = 0; j < mCollisionObjects.size(); ++j) {
            if (i == j)
                break;
            // Colliding cicles logic
            Fighter* f1 = mCollisionObjects[i];
            Fighter* f2 = mCollisionObjects[j];
            int xDistance = f1->mXCenter - f2->mXCenter;
            int yDistance = f1->mYCenter - f2->mYCenter;
            double centerDistance =
                sqrt(xDistance * xDistance + yDistance * yDistance);

            int sum = f1->mRadius + f2->mRadius;
            double surfaceDistance = (double)centerDistance - sum;
            if (surfaceDistance < 0) {
                // printf("Collision DETETECT!!");
                addCollision(f1, f2);
            }
        }

    dispatchCollisions();
}

void CollisionEngine::addCollision(Fighter* f1, Fighter* f2) {
    Collision newCollision(f1, f2);
    for (Collision existingCollision : mCollisions) {
        if (newCollision == existingCollision) {
            return;
        }
    }

    // printf("New collision added");
    mCollisions.push_back(newCollision);
}

void CollisionEngine::dispatchCollisions() {
    for (Collision c : mCollisions) {
        c.mF1->onCollision(c);
        c.mF2->onCollision(c);
    }
    mCollisions.clear();
}