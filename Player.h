#ifndef PLAYER_H
#define PLAYER_H

#include "Shared.h"
#include "Bullet.h"
#include <vector>

class Player : public Shared {
public:
    Player(int startX, int startY, int hp);
    void moveLeft();
    void moveRight(int boardWidth);
    void moveUp();
    void move_Down(int boardHeight);
    void shoot(std::vector<Bullet>& bullets);
};

#endif // PLAYER_H
