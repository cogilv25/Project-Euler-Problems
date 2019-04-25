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

//Please look at "Problem169 Pattern.txt" for some help trying to understand
//what I'm saying here as I trys to show how the pattern works visually there.
//
//The answer to this question for any single power of 2 is the power + 1:
//f(pow(2,n)) = n+1
//ex: 2->11->100 = 2+1 = 3 another: 5->44->433->4322->43211->432100 = 6
//
//Now if you take the difference between the powers and multiply them
//together you just have to take away (1 of the previous pattern) if that
//makes sense.
//
//Here is an equation for 3 powers of 2 named abc :
//		((c*b-1)*a-c)
//
//and 5 powers of 2 named abcde in that order: 
//		((((d*e-1)*c-e)*b-(d*e-1))*a-(d*e-1)*c-e


std::string Problem169::solution()
{ 
	nPowers = 19;
	ulong * prevAnswers = new ulong[nPowers];
	ulong ans = powers[nPowers - 1] + 1;
	prevAnswers[nPowers-1] = 1;
	for (int i = 1; i < nPowers; i++)
	{
		prevAnswers[nPowers-1-i] = ans;
		ans = ans * (powers[nPowers - 1 - i] - powers[nPowers - i] + 1) - prevAnswers[nPowers - i];
	}
	delete[] prevAnswers;
	return std::to_string(ans);
}