# CPP_Pointers


test your might

#easy
-switch the player to a pointer
-make it so the player cannot walk through walls
-- you may want to switch the player move to a bool are return messagesbased on successful movement
-get the monster to move towards the player once per move
- using the random function spawn 5 random walls in the maze avoid the players location
# medium 
-Get the monster to walk toward the player ending the game if it touches
-If the monster goes through a wall it will remove it from the game 
-Create a new class treasure that when the player touches the will get 100 points, if the monster touches the player gets -150 points 
-- To create a new class right click the sln file on the right **CPP_Pointers->New Class**, and type in the class name **Treasure**, you'll notice it auto populates the .h and .cpp file names, leave everything else as default and click ok.
--- for the start you can use ether the player or the monster as a base class to reference and begin the treasure placement. 
--- To spawn the treasure, you will need to **include the header in the CPP_Pointers.cpp** folder and you can see how we create the **player** on **line 15** 
# hard
Every time the treasure is collected, spawn a new one and 5 new walls 
Adjust the monster where is the Manhatten distance between the monster and the treasure is less then the distance to the player, the monster will seek to take the treasure over killing the player
# Coding standards
Both the player, monster, treasure and if you really want to break it down the walls, share some key aspects, Move, Icon, X, Y, can you create an abstract transform2D class for them to inherit from

