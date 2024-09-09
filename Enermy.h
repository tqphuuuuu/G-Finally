#ifndef ENERMY_H
#define ENERMY_H

#include "Shared.h"
#include <chrono>

using namespace std::chrono;

class Enermy : public Shared {
private:
    steady_clock::time_point lastMoveTime;
    int moveInterval;

public:
    Enermy(int startX, int startY, int hp, int dmg, int speed);
    void move(int boardWidth, int boardHeight);
};

#endif // ENERMY_H
