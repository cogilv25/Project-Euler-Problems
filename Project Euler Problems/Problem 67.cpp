#include "Problem67.h"
#include <fstream>

//7273 <- Just so I know if I break it


std::string Problem67::solution()
{
	std::ifstream file("../resources/triangle.txt");
	if (!file.is_open())
		return "Error: Unable to open file: ../resources/triangle.txt";

	factorial = new int[layers + 1];
	factorial[0] = 0;
	for (int i = 1; i < layers + 1; i++)
		factorial[i] = factorial[i - 1] + i;

	path = new int[factorial[layers]];
	char number[3];
	for (int i = 0; i < factorial[layers]; i++)
	{
		file.get(number, 3);
		//Throw away space or newline
		file.get();
		path[i] = std::stoi(number);
	}
	file.close();
	max(0);

	return std::to_string(path[0]);
}