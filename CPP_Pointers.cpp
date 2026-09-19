// CPP_Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "GameGrid.h"
#include "InputHandler.h"

int main()
{
    std::cout << "Hello World!\n";
    // create the game grid for the player
    GameGrid* grid = new GameGrid(30, 20);
    InputHandler* inpt = new InputHandler();
    Player p1;
    
    // Main gameplay loop
    while (true)
    {
        grid->MoveSymbol(p1.Icon(), p1.X(), p1.Y());
        // redraw our grid
        grid->DrawGrid();

        // check the input
        switch (inpt->GetInput("Use WASD to find treasure and escape the maze"))
        {
        case 'a':
        case 'A':
            p1.Move(0, -1);
            break;
        case 'd':
        case 'D':
            p1.Move(0, 1);
            break;
        case 's':
        case 'S':
            p1.Move(1, 0);
            break;
        case 'w':
        case 'W':
            p1.Move(-1, 0);
            break;
        default:
            cout << "Unkown input \n";
            break;
        }
    }
}


// things to do 
// implement a get char at pos function that 
