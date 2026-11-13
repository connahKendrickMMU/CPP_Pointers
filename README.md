# CPP_Pointers

Escape the monster maze, type W, A, S or D and press Enter to move one cell at a time.

## Overview


This is the sequel to the Hot and Cold game (CPP_PlayerClassExample). In that project every variable lived on the **stack**, this week the game board lives on the **heap**, and we will use pointers for three different jobs:

1. **Owning memory**, things made with **new** that we must **delete**
2. **Sharing a live object**, the monster holds a **Player\*** so it always sees where the player is now
3. **Avoiding includes**, a forward declaration (**class Player;**) is enough when you only need a pointer

## Where to find the scripts

Open **CPP_Pointers.sln** in Visual Studio, all the files are in the Solution Explorer on the right.

All the scripts are in the main solution folder, note the header files (for declaring) and the CPP (for implementation) are stored in seperate folders.


<!-- Images/Start.png goes here -->

## Task

### Step 1: Stopping the trail

<!-- video 2 link goes here -->
The grid only ever writes a symbol, it never rubs the old one out. In **GameGrid.h** add a new function under **MoveSymbol**:

```cpp
// put a blank back where something used to be
void ClearSymbol(int x, int y);
```

Then in **GameGrid.cpp** add the implementation at the bottom of the file:

```cpp
void GameGrid::ClearSymbol(int x, int y)
{
	// a space is an empty cell
	grid[x][y] = ' ';
}
```

Now in **CPP_Pointers.cpp**, straight after **grid->DrawGrid();** and before the **switch**, rub the player out before it moves:

```cpp
grid->ClearSymbol(p1.X(), p1.Y());
```

Run it again and the player should move without a trail. If the **P** disappears completely, you cleared it *after* **MoveSymbol** instead of before the move.

### Step 2: Putting the player on the heap

<!-- video 3 link goes here -->
At the top of **main** you will notice the grid and the input handler are made with **new**, so they live on the heap and we use **->** to talk to them, but the player is on the stack and uses a **dot**. Let's make the player match, change **Player p1;** to:

```cpp
Player* p1 = new Player();
```

You will get a few errors, each one is a **p1.** that now needs to be **p1->**, follow the error list to fix them. We also need a way to end the game so we can clean up our memory. Above the loop add a bool and change **while (true)** to use it:

```cpp
bool playing = true;
while (playing)
```

Then add a quit key to the **switch**:

```cpp
case 'q':
case 'Q':
    playing = false;
    break;
```

Finally, after the loop, everything we made with **new** needs a **delete**:

```cpp
// everything we made with new needs a delete
delete p1;
delete inpt;
delete grid;
```

The game should play exactly as before, and pressing **q** will now quit.

### Step 3: Walls block the player

<!-- video 4 link goes here -->
The player needs to *look* at the cell it wants to move into before it moves. First in **GameGrid.h** add a function to read a cell:

```cpp
// look but don't touch, tells us what is sitting in a cell
char GetCharAt(int x, int y);
```

And in **GameGrid.cpp**:

```cpp
char GameGrid::GetCharAt(int x, int y)
{
	return grid[x][y];
}
```

The player needs to know about the grid, but only as a pointer, so rather than including the whole header we can **forward declare** it. In **Player.h** add this above the class:

```cpp
class GameGrid; // forward declare, we only need a pointer so we don't need the full class
```

And in the public section:

```cpp
// peek at the cell we want to walk into before we go
bool CanMove(int DirX, int DirY, GameGrid* grid);
```

In **Player.cpp** add **#include "GameGrid.h"** under the existing include, as now we *do* call its functions, then add:

```cpp
bool Player::CanMove(int DirX, int DirY, GameGrid* grid)
{
	// walls say no
	return grid->GetCharAt(x + DirX, y + DirY) != '#';
}
```

Back in **CPP_Pointers.cpp**, rather than calling **Move** in every case, let the **switch** pick a direction and then move once after it:

```cpp
int dirX = 0;
int dirY = 0;
switch (inpt->GetInput("Use WASD to find treasure and escape the maze"))
{
case 'a':
case 'A':
    dirY = -1;
    break;
// repeat for other movements
}

if (p1->CanMove(dirX, dirY, grid))
    p1->Move(dirX, dirY);
```

Walk into any wall and the player should now stay put. If you get **use of undefined type 'GameGrid'** in **Player.cpp**, the include is missing, the forward declaration is only enough for the header.

### Step 4: A monster that chases you

<!-- video 5 link goes here -->
This is the important part. The monster isn't given the player's *position*, it's given **the player**, as a pointer, so every turn it reads where the player is *now*. Open **Monster.h**, it is currently empty, and replace it with:

```cpp
#pragma once
class Player; // forward declare, same trick as the player uses for the grid

class Monster
{
private:
	int x, y;
	char icon;
	Player* target; // we don't own this, we just watch it
public:
	Monster(int startX, int startY, Player* toChase);
	void Step();
	char Icon();
	int X();
	int Y();
};
```

Then in **Monster.cpp**:

```cpp
#include "Monster.h"
#include "Player.h"

Monster::Monster(int startX, int startY, Player* toChase)
{
	x = startX;
	y = startY;
	icon = 'M';
	target = toChase;
}

void Monster::Step()
{
	// the dumbest chase there is, close the gap one cell at a time
	// we read the player through the pointer, so we always see where they are now
	if (target->X() > x) x++;
	else if (target->X() < x) x--;
	else if (target->Y() > y) y++;
	else if (target->Y() < y) y--;
}

char Monster::Icon() { return icon; }
int Monster::X() { return x; }
int Monster::Y() { return y; }
```

In **CPP_Pointers.cpp** add **#include "Monster.h"** at the top, then after the player is made create the monster in the far corner, passing it the player:

```cpp
Monster* monster = new Monster(28, 18, p1);
```

Draw it next to the player's **MoveSymbol**, and rub it out next to the player's **ClearSymbol**:

```cpp
grid->MoveSymbol(monster->Icon(), monster->X(), monster->Y());
grid->ClearSymbol(monster->X(), monster->Y());
```

After the player moves, step the monster and check if it caught us:

```cpp
monster->Step();
if (monster->X() == p1->X() && monster->Y() == p1->Y())
{
    cout << "The monster got you!\n";
    playing = false;
}
```

Lastly add **delete monster;** to the clean up. Notice we delete the monster, but **never** the player through the monster's pointer, the monster never owned it.

Play-test it: an **M** starts bottom right and walks one cell towards you every turn, stand still against a wall and it will catch you. If the **M** smears, you've missed its **ClearSymbol**.

<!-- Images/End.png goes here -->

Try to work through the Challenges and ask for help if you get stuck.

## Hints

### The char\*\* grid, line by line

Open the **GameGrid** constructor in **GameGrid.cpp**:

```cpp
grid = new char* [x];        // an array of x pointers, one for each row
for (int i = 0; i < x; i++)
{
	grid[i] = new char[y];   // each row gets its own array of y characters
}
```

So **grid** is a pointer to the first of the row pointers, and each row pointer points at its own block of characters. **grid[2][5]** means "go to row 2, then go 5 along". That is **x + 1** uses of **new**, which matters when you write the destructor.

### Dot vs arrow

- **p1.X()** when **p1** is the object itself (stack)
- **p1->X()** when **p1** is a pointer to the object (heap), it means "go to the thing this points at, and call X on it"

### Forward declarations

A header that only **stores** a pointer doesn't need to know what is inside the class, so **class GameGrid;** is enough. The **.cpp** that actually **calls** a function on it does need the full class, so that is where the **#include** goes. This keeps headers light and stops two headers including each other in a loop.

## Challenges

Test your might

### Easy

- Write a destructor for the grid so it gives back its memory.

  Hint: declare **~GameGrid();** in **GameGrid.h**. In **GameGrid.cpp** you need a **loop** to **delete[]** each row, then **delete[]** the outer array. Look at the constructor, there is a **new** for every row. [Solution walkthrough](Solutions/CPP_Pointers%20Easy%20Solution%20Grid%20Destructor.docx)

- Give the player feedback, when they walk into a wall or type the wrong key, tell them.

  Hint: in **CPP_Pointers.cpp** add an **else** to the **CanMove** check, e.g. "A wall blocks your path". You could also make **Move** return a **bool** in **Player.h / .cpp**. [Solution walkthrough](Solutions/CPP_Pointers%20Easy%20Solution%20Player%20Feedback.docx)

- Spawn 5 random walls in the maze, avoiding the player's location.

  Hint: in **CPP_Pointers.cpp**, before the loop, use [rand](https://www.geeksforgeeks.org/cpp/rand-and-srand-in-ccpp/) to pick a cell and **MoveSymbol('#', ...)** to place it. Use **GetCharAt** to make sure the cell is empty first. [Solution walkthrough](Solutions/CPP_Pointers%20Easy%20Solution%20Random%20Walls.docx)

### Medium

- Create a new class **Treasure**, when the player touches it they get 100 points, if the monster gets to it first the player loses 150 points.

  To create a new class right click the project in the Solution Explorer **CPP_Pointers->Add->Class**, and type in the class name **Treasure**, you'll notice it auto populates the .h and .cpp file names, leave everything else as default and click ok. You can use the **Monster** as a reference for the position and icon. To spawn the treasure you will need to **include the header in CPP_Pointers.cpp**, and you can see how we create the **player** at the top of **main**. Use the **Score:** line at the bottom of the loop to show the score. [Solution walkthrough](Solutions/CPP_Pointers%20Medium%20Solution%20Treasure.docx)

- Once you have random walls, watch the monster, it rubs out any wall it walks over (why? look at what **ClearSymbol** does after it moves). Decide what should happen: either walls block the monster too, or smashing a wall is a feature that costs the monster a turn and prints a message.

  Hint: in **Monster.cpp**, the monster will need the grid, so pass it a **GameGrid\*** just like **CanMove** does. [Solution walkthrough](Solutions/CPP_Pointers%20Medium%20Solution%20Monster%20and%20Walls.docx)

- Give the player 3 lives, when the monster catches them they lose a life and respawn, the game only ends at 0.

  Hint: store the lives somewhere sensible (**Player.h** is a good start) and show them on the **Lives:** line in **CPP_Pointers.cpp**. [Solution walkthrough](Solutions/CPP_Pointers%20Medium%20Solution%20Lives.docx)

### Hard

- Every time the treasure is collected, spawn a new one and 5 new walls.
- If the [Manhattan distance](https://www.geeksforgeeks.org/data-science/manhattan-distance/) between the monster and the treasure is less than the distance to the player, the monster will go for the treasure instead of the player. Look at **Monster::Step()** in **Monster.cpp**, the monster will need a pointer to the treasure too.
- Waves: each time the treasure is collected another monster joins the hunt. Keep them in a list of **Monster\*** (a [vector](https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/) works well), and make sure every one of them is deleted at the end.

This is one way of doing the task, if you prefer trying other techniques feel free.

### Refinements

Part of the assignment and purpose of this module is to show you can refine the gameplay to a high standard.

- Add some colour, with the [**system("Color 0E");**](https://www.geeksforgeeks.org/cpp/how-to-print-colored-text-in-c/) command you can change the console text (E for text, 0 for background).
- Limit the number of moves the player can make before the game ends, show the moves left next to the score, and give some bonus moves for collecting treasure.
- Add a new refinement to the game of your own choosing.

### Coding Practices

- The player, monster, treasure and, if you really want to break it down, the walls all share some key aspects: **Move**, **Icon**, **X** and **Y**. Can you create an abstract **Transform2D** class for them to inherit from?
- See if you can make a Gameplay Manager that handles the score, lives and game state.
- Every **new** needs a **delete**, unless you let C++ do it for you. Try swapping the raw pointers in **main** for a [unique_ptr](https://www.geeksforgeeks.org/cpp/unique_ptr-in-cpp/), which deletes itself when it goes out of scope.

# Reference
Content is made by Connah Kendrick (Connah.Kendrick@mmu.ac.uk)
