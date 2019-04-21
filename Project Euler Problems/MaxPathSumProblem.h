#pragma once
#include "Problem.h"

class MaxPathSumProblem : public Problem
{
protected:
	int layers;
	int *factorial, *path;

	int max();
	void generateFactorials(int n);
public:
	virtual ~MaxPathSumProblem() {};
};