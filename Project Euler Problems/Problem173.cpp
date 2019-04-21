#include "Problem173.h"
//1572729 <- Just so I know if I break it

std::string Problem173::solution()
{
	int tiles = 1000000, count = 0;

	//Start with the biggest possible outer and inner squares.
	//Decrease the inner square's width until the outer square
	//area minus the inner square area is greater than the max
	//tiles. Then decrease the outer width by one and repeat until
	//the outer width is the minimum width of a laminae (3)
	for (int outer = tiles / 4 + 2; outer >= 3; outer --)
		for (int inner = outer - 2; inner > 0; inner -= 2)
		{
			if (outer * outer - inner * inner > tiles)
				break;
			count++;
		}
	return std::to_string(count);
}