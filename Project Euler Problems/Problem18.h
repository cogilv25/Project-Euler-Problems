#pragma once
#include "MaxPathSumProblem.h"

class Problem18 : public MaxPathSumProblem {
public:
	std::string solution();
	Problem18()
	{ 
		name = "Maximum path sum I"; 
		layers = 15; 
	}
	~Problem18()
	{ 
		delete[] layerStartIndices;
	}
};