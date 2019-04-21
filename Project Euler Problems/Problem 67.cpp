#include "Problem67.h"
#include <fstream>
//7273 <- Just so I know if I break it


bool Problem67::loadFile(std::string filename)
{
	std::ifstream file("../resources/triangle.txt");
	if (!file.is_open())
		return false;

	//2 digits + null termination
	char number[3];
	for (int i = 0; i < factorial[layers]; i++)
	{
		file.get(number, 3);
		//Throw away space or newline
		file.get();
		path[i] = std::stoi(number);
	}
	file.close();
	return true;
}

std::string Problem67::solution()
{
	generateFactorials(layers + 1);
	path = new int[factorial[layers]];

	if(!loadFile("../resources/triangle.txt"))
		return "Error: Unable to open file: ../resources/triangle.txt";

	return std::to_string(max());
}