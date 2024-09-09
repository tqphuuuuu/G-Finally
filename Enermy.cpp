#include "Enermy.h"

Enermy::Enermy(int startX, int startY, int hp, int dmg, int speed)
    : Shared(startX, startY, hp, dmg), moveInterval(speed) {
    lastMoveTime = steady_clock::now();
}

void Enermy::move(int boardWidth, int boardHeight) {
    auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(currentTime - lastMoveTime).count();

    if (elapsedTime >= moveInterval) {
        int direction = rand() % 4;
        switch (direction) {
        case 0:
            if (y > 0) y--;
            break;
        case 1:
            if (y < boardHeight - 1) y++;
            break;
        case 2:
            if (x > 0) x--;
            break;
        case 3:
            if (x < boardWidth - 1) x++;
            break;
        }
        lastMoveTime = currentTime;
    }
}
