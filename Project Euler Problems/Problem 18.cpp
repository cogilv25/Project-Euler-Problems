#include "Problem18.h"
//TODO: current and lower should probably be pointers
//1074 <- Just so I know if I break it

int problem18Data[]{
75,
95, 64,
17, 47, 82,
18, 35, 87, 10,
20, 4, 82, 47, 65 ,
19, 1, 23, 75, 3, 34,
88, 2, 77, 73, 7, 63, 67,
99, 65, 4, 28, 6, 16, 70, 92,
41, 41, 26, 56, 83, 40, 80, 70, 33,
41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23 };



//We can't find the max for this layer until we know the max for
//the layer below it.
void Problem18::max(int layer)
{
	if (layer < layers-2)
		max(layer + 1);
	//These are not strictly necessary but they make things more
	//clear and will be optimised out by the compiler anyway.
	int current = factorial[layer];
	int lower = factorial[layer + 1];
	for (int i = 0; i < layer + 1; i++)
	{
		path[current + i] += path[lower + i] > path[lower + i + 1] ? path[lower + i] : path[lower + i + 1];
	}
}

std::string Problem18::solution()
{
	path = problem18Data;
	factorial = new int[layers];
	factorial[0] = 0;
	for (int i = 1; i < layers; i++)
		factorial[i] = factorial[i - 1] + i;

	max(0);
	
	return std::to_string(path[0]);
}
