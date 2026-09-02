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
        // check the input
        switch (inpt->GetInput("Use WASD to escape the maze"))
        {
        case 'a':
        case 'A':
            
        default:
            cout << "Unkown input \n";
            break;
        }

        // redraw our grid
        grid->DrawGrid();
    }
}


// things to do 
// implement a get char at pos function that 
