#include "Problem18.h"
#include "Problem54.h"
#include "Problem67.h"
#include "Problem173.h"
#include "Problem169.h"
#include <iostream>
#include <map>

std::map<int, Problem*> problems;

int main(int argc, char ** argv)
{
	problems[18] = new Problem18();
	problems[54] = new Problem54();
	problems[67] = new Problem67();
	problems[173] = new Problem173();
	problems[169] = new Problem169();

	if (argc == 2)
	{
		try
		{
			int key = std::stoi(argv[1]);
			auto p = problems.find(key);
			if (!(p == problems.end()))
			{
				std::cout << p->second->name << " (Problem " << p->first << "): " << std::endl;
				std::cout << p->second->solution() << std::endl << std::endl;
			}
			else
			{
				std::cout << "Error: Problem does not exist or has not been solved" << std::endl << std::endl;
				std::cin.ignore(10000, '\n');
				return -1;
			}
		}
		catch(std::exception e)
		{
			std::cout << "Error: " << e.what();
			std::cin.ignore(10000, '\n');
			return -1;
		}
	}
	else
	{
		std::cout << "Usage: Euler [problem number]" << std::endl;
		std::cout << "Press enter to run all problems..." << std::endl;
		std::cin.ignore(10000, '\n');

		for (auto f : problems)
		{
			std::cout << f.second->name << " (Problem " << f.first << "): " << std::endl;
			std::cout << f.second->solution() << std::endl << std::endl;
		}
	}

	std::cout << "Press enter to exit application..." << std::endl;
	std::cin.ignore(10000, '\n');

	for (auto f : problems)
		delete f.second;

	return 0;
}