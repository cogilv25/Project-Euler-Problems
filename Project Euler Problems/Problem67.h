#pragma once
#include "Problem18.h"

class Problem67 : public Problem18 {
public:
	Problem67() {
		name = "Maximum path sum II";
		layers = 100; 
	};
	~Problem67() { delete[] path; };
	std::string solution();
};