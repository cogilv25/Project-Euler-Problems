#include "MaxPathSumProblem.h"


int MaxPathSumProblem::max()
{
	//We can't find the max for any layer until we know the max for
	//the layer below it so we start at the bottom.
	for (int layer = layers - 2; layer >= 0; layer--)
	{
		int *current = path + layerStartIndices[layer];
		int *lower = path + layerStartIndices[layer + 1];
		for (int i = 0; i < layer + 1; i++)
		{
			current[i] += lower[i] > lower[i + 1] ? lower[i] : lower[i + 1];
		}
	}
	return path[0];
}

void MaxPathSumProblem::generateLayerStartIndices(int n)
{
	layerStartIndices = new int[n];
	layerStartIndices[0] = 0;
	for (int i = 1; i < n; i++)
		layerStartIndices[i] = layerStartIndices[i - 1] + i;
}
