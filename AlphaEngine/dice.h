#include<iostream>

enum Turn { PlayerTurn, EnemyTurn };
int TotalAttack = 0;
int TotalDefence = 0;

int performRoll(Turn turn);
void checkRoll(int die, Turn turn);
void gameTurn(Turn turn);
