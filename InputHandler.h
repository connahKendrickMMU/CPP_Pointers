#pragma once
#include <string>

// no "using namespace std;" in a header, every file that includes this would get it too
// so we write std:: in full here and put the using in the .cpp instead

class InputHandler
{
private:
	std::string inpt;
public:
	char GetInput(std::string message);
};

