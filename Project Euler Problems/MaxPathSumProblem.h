#pragma once
#include "Problem.h"

class MaxPathSumProblem : public Problem
{
protected:
	int layers;
	int *layerStartIndices, *path;

	int max();
	void generateLayerStartIndices(int layers);
public:
	virtual ~MaxPathSumProblem() {};
};