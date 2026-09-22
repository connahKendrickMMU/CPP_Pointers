#include "GameGrid.h"
#include <iostream>
using namespace std;


GameGrid::GameGrid(int x, int y)
{
	// create our game grid that we can manipulation
	sizeX = x;
	sizeY = y;

	grid = new char* [x]; // set the number of rows y goes down
	for (int i = 0; i < x; i++)
	{
		grid[i] = new char[y]; // set the new x goes across
	}
	// set the base values
	for (int i = 0; i < x; i++)
	{
		for (int o = 0; o < y; o++)
		{
			if (i == 0 || i == x - 1)
				grid[i][o] = '#';
			else if (o == 0 || o == y - 1)
				grid[i][o] = '#';
			else
				grid[i][o] = ' ';
		}
	}
	DrawGrid();
}

void GameGrid::DrawGrid()
{
	// clear the screen (\033[2J clears, \033[H reset cursor)
	cout << "\033[2J\033[H";
	for (int i = 0; i < sizeX; i++)
	{
		for (int o = 0; o < sizeY; o++)
			cout << grid[i][o];
		cout << '\n';
	}

}

void GameGrid::MoveSymbol(char object, int newX, int newY)
{
	// this will work for single items, e.g. player, monster cash
	grid[newX][newY] = object;
}