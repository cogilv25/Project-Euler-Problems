#include "Problem173.h"

//1572729 <- Just so I know if I break it

std::string Problem173::solution()
{
	int tiles = 1000000, count = 0;

	for (int outer = 3; outer < tiles / 4 + 2; outer++)
		for (int inner = outer - 2; inner > 0; inner -= 2)
		{
			if (outer*outer - inner * inner > tiles)
				break;
			count++;
		}
	return std::to_string(count);
}