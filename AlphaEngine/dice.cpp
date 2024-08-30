#include<iostream>
#include "dice.h"

int TotalAttack = 0;
int TotalDefence = 0;

int performRoll(Turn turn) {
	//char choice;
	int first = 0;
	int second = 0;
	const char* current = turn == PlayerTurn ? "Player" : "Enemy";
	std::cout << current << "'s turn" << std::endl;

	first = 1 + (rand() % 6); 
	second = 1 + (rand() % 6);
	
	int result = first * 10 + second;
	return result;
}


void checkRoll(int res, Turn turn) {
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
