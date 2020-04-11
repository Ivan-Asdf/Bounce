#include "core/game_object.h"

class PlayerBall : public Ball {
public:
    PlayerBall(Ball* ball);
    void move(int x, int y);
};