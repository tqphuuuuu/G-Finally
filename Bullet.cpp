#include "Bullet.h"
#include<chrono>

Bullet::Bullet(int x, int y, int dmg, int interval) : Shared(x, y, 0, dmg), moveInterval(interval) {
    lastMoveTime = steady_clock::now();
}

void Bullet::move() {
    auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(currentTime - lastMoveTime).count();

    if (elapsedTime >= moveInterval) {
        y--;
        lastMoveTime = currentTime;
    }
}

bool Bullet::isOutOfScreen(int screenHeight) {
    return y < 0;
}
