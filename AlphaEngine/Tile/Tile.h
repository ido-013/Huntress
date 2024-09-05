#pragma once
#include <string>

const int tileCount = 3;

class Tile
{
public:
	static std::string const squareTiles[tileCount];
	static std::string const rightTriTiles[tileCount];
	static std::string const leftTriTiles[tileCount];

	static void ChangeTile(int i);
	static void ChangeTile();
};