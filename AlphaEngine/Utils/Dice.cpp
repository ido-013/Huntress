#include "Dice.h"
#include <iostream>

int TotalAttack = 0;
int TotalDefence = 0;

int PerformRoll() {
	int first = 0;
	int second = 0;

	first = 1 + (rand() % 6); 
	second = 1 + (rand() % 6);
	
	int result = first * 10 + second;
	return result;
}


void CheckRoll(int res, Turn turn) {
	int first = res / 10;
	int second = res % 10;
		
	std::cout << "You rolled a: " << res << std::endl;
		if (turn == PlayerTurn) {
			TotalAttack += first;
			TotalDefence += second;
			std::cout << "Player Damage is: " << TotalAttack << std::endl;
			std::cout << "Attack:  " << TotalAttack << " Defence: " << TotalDefence << "]" << "\n\n" << std::endl;
		}
		else {
			TotalAttack += first;
			std::cout << "Enemy Damage is: " << TotalAttack << std::endl;
			std::cout << "Attack: " << TotalAttack << " Defence: " << TotalDefence << "]" << "\n\n" << std::endl;
		}
}
