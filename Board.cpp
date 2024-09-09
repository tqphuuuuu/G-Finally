#include "Board.h"

using namespace std;
using namespace chrono;

Board::Board(int w, int h, int hp, int numberEnermy, int hp_chicken, int dmg_chicken, int sp_Chicken)
    : width(w), height(h), player(w / 2, h - 1, hp), frameCount(0), fps(0), lastFPS(0), numberenemies(numberEnermy), health_Chicken(hp_chicken), dmg_Chicken(dmg_chicken), speed_Chicken(sp_Chicken) {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Board::clearScreen() {
    system("cls");
}

void Board::setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void Board::setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void Board::displayFPS() {
    setCursorPosition(width + 3, 0);
    setColor(7);
    cout << "FPS: " << fps;

    setCursorPosition(width + 2, 1);
    setColor(7);
    cout << "Health: " << player.health << endl;

    setCursorPosition(width + 2, 2);
    setColor(7);
    cout << "Points: " << point << endl;

    setCursorPosition(0, height + 2);
}

void Board::SpawnChicken() {
    if (!hasEnemyOnBoard()) {
        for (int i = 0; i < numberenemies; ++i) {
            int spawnX = rand() % width; // Vị trí xuất hiện ngẫu nhiên của kẻ thù
            enemies.emplace_back(spawnX, 0, health_Chicken, dmg_Chicken, speed_Chicken);
        }
    }
}

bool Board::hasEnemyOnBoard() {
    return !enemies.empty();
}

void Board::input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a') {
            player.moveLeft();

        }
        else if (key == 'd') {
            player.moveRight(width);
        }
        else if (key == 'w') {
            player.moveUp();
        }
        else if (key == 's') {
            player.move_Down(height);
        }
        else if (key == ' ') {
            PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
            player.shoot(bullets);

        }
    }
}

void Board::upDate() {
    for (auto& bullet : bullets) {
        bullet.move(); // Di chuyển đạn
    }

    for (auto& chicken : enemies) {
        chicken.move(width, height); // Di chuyển kẻ thù
    }

    for (auto& chicken : enemies) {
        if (chicken.x == player.x && chicken.y == player.y) {
            player.takeDamage(chicken.damage); // Người chơi bị tấn công bởi kẻ thù
        }
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletHit = false;
        for (auto chickenIt = enemies.begin(); chickenIt != enemies.end();) {
            if (bulletIt->x == chickenIt->x && bulletIt->y == chickenIt->y) {
                chickenIt->takeDamage(bulletIt->damage); // Kẻ thù bị tấn công bởi đạn
                bulletHit = true;

                if (chickenIt->isDead()) {
                    point++;
                    chickenIt = enemies.erase(chickenIt); // Xóa kẻ thù bị tiêu diệt
                }
                else {
                    ++chickenIt;
                }
            }
            else {
                ++chickenIt;
            }
        }

        if (bulletHit) {
            bulletIt = bullets.erase(bulletIt); // Xóa đạn đã trúng kẻ thù
        }
        else if (bulletIt->isOutOfScreen(height)) {
            bulletIt = bullets.erase(bulletIt); // Xóa đạn ra ngoài màn hình
        }
        else {
            ++bulletIt;
        }
    }

    if (player.isDead()) {

        cout << "Game Overrrr";


        exit(0); // Kết thúc trò chơi khi người chơi chết
    }
    SpawnChicken(); // Sinh kẻ thù mới nếu không có kẻ thù trên bảng

}

void Board::render() {
    auto startRenderTime = steady_clock::now(); // Thời điểm bắt đầu render
    clearScreen(); // Xóa màn hình console

    setColor(11); // Set màu cyan cho bảng

    for (int i = 0; i < width + 2; i++) cout << '#';
    cout << endl;

    for (int y = 0; y < height; ++y) {
        cout << '#';
        for (int x = 0; x < width; ++x) {
            bool drawn = false;

            for (const auto& chicken : enemies) {
                if (chicken.x == x && chicken.y == y) {
                    setColor(12); // Gà màu đỏ
                    cout << 'G';
                    setColor(11);
                    drawn = true;
                    break;
                }
            }

            if (!drawn) {
                for (const auto& bullet : bullets) {
                    if (bullet.x == x && bullet.y == y) {
                        setColor(14); // Đạn màu vàng
                        cout << '@';
                        setColor(11);
                        drawn = true;
                        break;
                    }
                }
            }

            if (!drawn) {
                if (player.x == x && player.y == y) {
                    setColor(10); // Màu của nhân vật là xanh lá
                    cout << '^';
                    setColor(11);
                    drawn = true;
                }
            }

            if (!drawn) {
                cout << ' ';
            }
        }
        cout << '#' << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << '#';
    cout << endl;
    displayFPS(); // Hiển thị FPS và thông tin khác
    auto endRenderTime = steady_clock::now(); // Thời điểm kết thúc render
    auto renderTime = duration_cast<milliseconds>(endRenderTime - startRenderTime).count(); // Thời gian đã trôi qua trong quá trình render
    if (renderTime < 1000 / 60) {
        this_thread::sleep_for(milliseconds(1000 / 60 - renderTime)); // Ngủ đủ thời gian để duy trì 60 FPS

    }
    fps = 890 / static_cast<double>(renderTime); // Tính FPS hiện tại



}

void Board::run() {
    lastFrameTime = steady_clock::now();

    while (player.health > 0) {
        input();
        upDate();
        render();/*
        frameCount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));*/
    }

    cout << "Game Over! Your score: " << point << endl;
}
