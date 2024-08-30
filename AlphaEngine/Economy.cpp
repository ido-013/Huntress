#include "Economy.h"
#include <random>
enum Enemy {
    normal,
    elite,
    boss
};
int money = 0;
int round = 0;
void GameStart()
{
    money = 12;
    return;
}

void EarnPrize(int round,int unittype)
{
    switch (unittype) {
    case normal:
        money += 8;
        money += 1 + (rand() % 6);
        break;
    case elite:
        money += 15;
        money += 2 + (rand() % 6) + (rand() % 6);
        break;
    case boss:
        money += 25;
        money += 3 + (rand() % 6) + (rand() % 6) + (rand() % 6);
        break;
    }

    round++;
    
}
