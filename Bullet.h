#ifndef BULLET_H
#define BULLET_H

#include "Shared.h"
#include <chrono>

using namespace std::chrono;

class Bullet : public Shared {
private:
    steady_clock::time_point lastMoveTime;
    int moveInterval;

public:
    Bullet(int x, int y, int dmg, int interval);
    void move();
    bool isOutOfScreen(int screenHeight);
};

#endif // BULLET_H
