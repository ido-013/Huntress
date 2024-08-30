#pragma once
#include <iostream>

enum Turn { PlayerTurn, EnemyTurn };

int performRoll(Turn turn);
void checkRoll(int die, Turn turn);
void gameTurn(Turn turn);
