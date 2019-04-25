#include "Problem67.h"
#include <fstream>
//484 * 15 + 13 <- Just so I know if I break it

/*
TODO:
1)I should have a try catch around stoi or at least comment that the problem
	guarantees no mistakes in the file.

*/

bool Problem67::loadFile(std::string filename)
{
	std::ifstream file("../resources/triangle.txt");
	if (!file.is_open())
		return false;

	//2 digits + null termination
	char number[3];
	for (int i = 0; i < layerStartIndices[layers]; i++)
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
	generateLayerStartIndices(layers + 1);
	path = new int[layerStartIndices[layers]];

	if(!loadFile("../resources/triangle.txt"))
		return "Error: Unable to open file: ../resources/triangle.txt";

	return std::to_string(max());
}