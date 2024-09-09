﻿#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "Bullet.h"
#include "Enermy.h"
#include <iostream>
#include <thread>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <mmsystem.h>
#include <SDL.h>
#pragma comment(lib, "winmm.lib")


using namespace std;
class Board {
private:
    int width, height;
    int health;
    int numberenemies;
    int health_Chicken;
    int dmg_Chicken;
    int point;
    int speed_Chicken;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enermy> enemies;
    std::chrono::steady_clock::time_point lastFrameTime;
    int frameCount;
    int fps;
    int lastFPS;
    bool loopSound;
    HANDLE hConsole;

    void clearScreen();
    void setCursorPosition(int x, int y);
    void setColor(int color);
    void displayFPS();
    void SpawnChicken();
    bool hasEnemyOnBoard();
   

public:
    Board(int w, int h, int hp, int numberEnermy, int hp_chicken, int dmg_chicken, int sp_Chicken);
    void input();
    void upDate();
    void render();
    void run();
};
#endif // BOARD_H