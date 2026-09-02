#pragma once
#include "Player.h"

class GameGrid
{
public:
	// constructor builds the game grid
	GameGrid(int rows, int height);
	void DrawGrid();
	bool MoveAndPlacePlayer(Player p1, int xDir, int yDir);
private:
	int sizeX, sizeY;
	// a pointer to pointers
	char** grid; 

};

