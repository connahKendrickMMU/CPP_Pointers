#include "InputHandler.h"
#include <iostream>

using namespace std;

char InputHandler::GetInput(string message)
{
	cout << message << "\n";
	cin >> inpt;

	if (inpt.length() < 1)
	{
		return ' ';
	}
	else
	{
		return inpt[0];
	}
}