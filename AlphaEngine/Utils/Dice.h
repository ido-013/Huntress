#pragma once

enum Turn { PlayerTurn, EnemyTurn };

int PerformRoll();
void CheckRoll(int die, Turn turn);
