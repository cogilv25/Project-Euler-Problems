#pragma once

#include <string>
#include <vector>

class Problem
{
public:
	virtual std::string solution() = 0;
	std::string name;
	virtual ~Problem() {};
};
