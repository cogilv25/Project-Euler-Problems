#include "Problem169.h"
#define ulong unsigned long long
//444412618 * 402 + 371 <- Just so I know if I break it

/*
TODO:
1)Rename variables to make things more clear

2)base10 to base2 converter

3)explanation

*/


//I will work this out programatically later but for now
//here is the binary for 10^25:
//100001000101100101010001011000010100000000010100100001001010000000000000000000000000
//
//So therefore the maximum powers of 2 for 10^25 are:
ulong powers[]{ 83,78,74,72,71,68,66,64,60,58,57,52,50,40,38,35,30,27,25 };

//This will go when I add the base10 to base2 converter
#define n 19

//I will add an explanation to this later but for now look at
//"Problem169 Pattern.txt" to get an idea of how this works
std::string Problem169::solution()
{ 
	ulong prevAnswers[n], ans = powers[n - 1] + 1;
	prevAnswers[n-1] = 1;
	for (int i = 1; i < n; i++)
	{
		prevAnswers[n-1-i] = ans;
		ans *= (powers[n - 1 - i] - powers[n - i] + 1);
		ans -= prevAnswers[n - i];
	}

	return std::to_string(ans);
}