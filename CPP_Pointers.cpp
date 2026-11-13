// CPP_Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "GameGrid.h"
#include "InputHandler.h"

// same as the hot and cold game, saves us typing std:: in front of cout
using namespace std;

int main()
{
    std::cout << "Find your treasure adventurer! but avoid the monster lurking in the shadows!\n";
    // create the game grid for the player
    GameGrid* grid = new GameGrid(10, 10);
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
            cout << "Unknown input \n";
            break;
        }
        // students: this is a placeholder, the treasure and lives challenges fill it in
        cout << "Score: " << "" << "\t" << "Lives: " << "\n";
    }
}


// things to do
// the player can walk through walls, in step 3 you add a GetCharAt function to the grid to stop it
