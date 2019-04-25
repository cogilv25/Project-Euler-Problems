#include "Problem67.h"
#include <fstream>
//484 * 15 + 13 <- Just so I know if I break it

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
	layers = 100;
	generateLayerStartIndices(layers + 1);
	path = new int[layerStartIndices[layers]];

	try {
		if (!loadFile("../resources/triangle.txt"))
			return "Error: Unable to open file: ../resources/triangle.txt";
	}
	catch (std::exception e)
	{
		return e.what();
	}

	return std::to_string(max());
}