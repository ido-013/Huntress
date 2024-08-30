#include<iostream>
#include "dice.h"


int performRoll(Turn turn) {
	char choice;
	int first = 0;
	int second = 0;
	const char* current = turn == PlayerTurn ? "Player" : "Enemy";
	//std::cout << current << "'s turn" << std::endl;

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


////function for a player's gameturn
//void gameTurn(Turn turn) {
//	int die = performRoll(turn);
//	checkRoll(die, turn);
//}


//int main() {
//	char mainChoice;//for user input from main menu
//	enum Player player = PA;
//
//	cout << "Welcome to The Dice Game! Please select from the following menu: " << endl;
//	cout << "Press [p] to play, [q] to quit \n\n";
//
//	cin >> mainChoice;
//
//	if (mainChoice == 'p' || mainChoice == 'P') {
//
//		//game runs until one of the total scores is 100
//		while (true)
//		{
//			//gameturns alternating
//			gameTurn(PA);
//			//Checks if PlayerA won yet 
//			if (totalScoreA >= 100) {
//				cout << "CONGRATULATIONS********* PLAYER A IS THE WINNER !! *********CONGRATULATIONS\n";
//				exit(EXIT_SUCCESS);//Exits the appliction
//			}
//
//			gameTurn(PB);
//			if (totalScoreB >= 100) {
//				cout << "CONGRATULATIONS********* PLAYER B IS THE WINNER !! *********CONGRATULATIONS\n";
//				exit(EXIT_SUCCESS);
//			}
//		}
//	}
//	else if (mainChoice == 'q' || mainChoice == 'Q')
//	{
//		exit(EXIT_SUCCESS);
//	}


