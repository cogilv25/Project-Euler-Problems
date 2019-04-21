#pragma once
#include "Problem.h"

class Problem18 : public Problem {
protected:
	int layers = 15;
	int *factorial, *path;
	void max(int layer = 0);
public:
	virtual std::string solution();
	virtual ~Problem18() { delete[] factorial; };
	Problem18() { name = "Maximum path sum I"; }
};