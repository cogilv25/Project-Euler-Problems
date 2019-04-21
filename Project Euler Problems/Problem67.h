#pragma once
#include "Problem18.h"

class Problem67 : public MaxPathSumProblem {
private:
	bool loadFile(std::string filename);
public:
	std::string solution();
	Problem67()
	{
		name = "Maximum path sum II";
		layers = 100;
	}
	~Problem67()
	{ 
		delete[] path; 
		delete[] factorial; 
	}
};