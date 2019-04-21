#pragma once
#include "Problem.h"

class Problem54 : public Problem {
private:
	int cardValueToInt(char value);
	std::vector<int> getHandRank(std::vector<int> hand, int * count, bool flush);
	bool player1Wins(char* round);
public:
	std::string solution();
	Problem54() { name = "Poker hands"; };
};