#ifndef BOSS_H
#define BOSS_H

#include "Enermy.h"

class Boss : public Enermy {
public:
    Boss(int startX, int startY);
    // Ghi đè các hàm khác hoặc thêm các hàm mới nếu cần
};

#endif // BOSS_H
