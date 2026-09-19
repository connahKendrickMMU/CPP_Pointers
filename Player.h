#pragma once
class Player
{
// store the player position and icon
private:
	int x, y;
	char icon;
public:
	Player();
	void Move(int DirX, int DirY);
	char Icon();
	int X(); 
	int Y();

};

