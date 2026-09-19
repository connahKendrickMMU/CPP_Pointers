#pragma once

class GameGrid
{
public:
	// constructor builds the game grid
	GameGrid(int rows, int height);
	void DrawGrid();
	void MoveSymbol(char object, int newX, int newY);
private:
	int sizeX, sizeY;
	// a pointer to pointers
	char** grid; 

};

