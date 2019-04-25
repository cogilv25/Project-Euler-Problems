#pragma once
#include "Problem.h"
class Problem169 : public Problem
{
private:
	int nPowers;
public:
	std::string solution();
	Problem169() { name = "Sums of powers of 2"; }
};

