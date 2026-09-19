#include "Player.h"

Player::Player()
{
	x = 1;
	y = 1; 
	icon = 'P';
} 

char Player::Icon()
{
	return icon;
}

int Player::X()
{
	return x;
}

int Player::Y()
{
	return y;
}

void Player::Move(int DirX, int DirY)
{
	// offset the player
	x += DirX;
	y += DirY;
}