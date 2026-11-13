#pragma once

class GameGrid
{
public:
	// constructor builds the game grid, x is the number of rows (down) and y the columns (across)
	GameGrid(int rows, int columns);
	void DrawGrid();
	void MoveSymbol(char object, int newX, int newY);
private:
	int sizeX, sizeY;
	// a pointer to pointers
	char** grid; 

};

