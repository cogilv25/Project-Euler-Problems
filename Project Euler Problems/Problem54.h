#pragma once
#include "Problem.h"

struct Hand
{
	bool flush = true;
	std::vector<int> cards{ 0,0,0,0,0 };
	//How many of each card value is in the
	//hand (for counting pairs, threes, etc)
	int counts[14]{ 0 };
};

class Problem54 : public Problem {
private:
	Hand hands[2000];
	int rounds = 1000;

	bool loadFile(std::string filename);
	bool isPlayer1Winner(Hand playerHand, Hand opponentHand);
	int cardValueToInt(char value);
	bool getStraight(Hand hand);
	std::vector<int> getRank(Hand hand);

public:
	std::string solution();
	Problem54() { name = "Poker hands"; };
};