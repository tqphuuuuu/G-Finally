#include "Player.h"

Player::Player(int startX, int startY, int hp) : Shared(startX, startY, hp, 1) {}

void Player::moveLeft() {
    if (x > 0) x--;
}

void Player::moveRight(int boardWidth) {
    if (x < boardWidth - 1) x++;
}

void Player::moveUp() {
    if (y > 0) y--;
}

void Player::move_Down(int boardHeight) {
    if (y < boardHeight - 1) y++;
}

void Player::shoot(std::vector<Bullet>& bullets) {
    bullets.emplace_back(x, y, damage, 100);
}
