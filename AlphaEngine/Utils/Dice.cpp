#include "Dice.h"
#include <iostream>

static int PerformRoll() {
	int result = 1 + (rand() % 6);
	return result;
}