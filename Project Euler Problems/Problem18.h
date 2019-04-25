#pragma once
#include "MaxPathSumProblem.h"

class Problem18 : public MaxPathSumProblem {
public:
	std::string solution();
	Problem18(){ name = "Maximum path sum I"; }
	~Problem18()
	{ 
		delete[] layerStartIndices;
	}
};