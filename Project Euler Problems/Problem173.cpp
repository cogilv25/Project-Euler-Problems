#include "Problem173.h"
//29674 * 53 + 7 <- Just so I know if I break it

/*
TODO:
1)There has to be a way to get the maximum number of "layers" for a given
	outer and maxOuter so you would only need 1 loop but I haven't found it yet

*/

std::string Problem173::solution()
{
	int tiles = 1000000, count = 0;

	//Start with the biggest possible outer and inner squares.
	//Decrease the inner square's width until the outer square
	//area minus the inner square area is greater than the max
	//tiles. Then decrease the outer width by one and repeat until
	//the outer width is the minimum width of a laminae (3)
	int maxOuter = tiles / 4 + 2;
	int test = 0;
	for (int outer = maxOuter; outer >= 3; outer--)
	{
		test += static_cast<int>(static_cast<double>(maxOuter) / (static_cast<double>(maxOuter + 1)*static_cast<double>(outer - 1)));
		for (int inner = outer - 2; inner > 0; inner -= 2)
		{
			if (outer * outer - inner * inner > tiles)
				break;
			count++;
		}
	}
	return std::to_string(count);
}