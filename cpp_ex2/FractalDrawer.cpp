#include <iostream>
#include <fstream>
#include <regex>
#include "Fractal.h"

#define INPUT "Invalid input"
#define USAGE "Usage: FractalDrawer <file path>"

int usage_error()
{
	std::cerr << USAGE << std::endl;
	exit(EXIT_FAILURE);
}

int input_error()
{
	std::cerr << INPUT << std::endl;
	exit(EXIT_FAILURE);
}

bool goodInput(const std::string& line)
{
	return (line.length() == 3 &&
			 line[1] == ',' &&
			 isdigit(line[0]) &&
			 isdigit(line[2]) &&
			 0 < (line[0]) - '0' &&
			 line[0] - '0' < 4 &&
			 0 < line[2] - '0' &&
			 line[2] - '0' < 7);
}

void parseFile(int argc, char *const *argv, std::stack<std::pair<int,int>>& data)
{
	if (argc != 2)
	{
		usage_error();
	}
	std::ifstream infile;
	infile.open(argv[1]);
	if (!infile)
	{
		input_error();
	}
	std::string line;
	while (getline(infile, line))
	{
		if (!goodInput(line))
		{
			input_error();
		}
		data.push(std::make_pair(line[0] - '0', line[2] - '0'));
	}
	infile.clear();
}


void printFractals(std::stack<std::pair<int,int>> &data)
{
	int type, dim;
	while (!data.empty())
	{
		type = std::get<0>(data.top());
		dim = std::get<1>(data.top());
		switch (type)
		{
			case 1:
			{
				auto carpet = Carpet(dim);
				carpet.print();
				break;
			}
			case 2:
			{
				auto sieve = Sieve(dim);
				sieve.print();
				break;
			}
			case 3:
			{
				auto cantor = Cantor(dim);
				cantor.print();
				break;
			}
			default:
				break;
		}
		std::cout << std::endl;
		data.pop();
	}
}

int main(int argc, char **argv)
{
	std::stack<std::pair<int,int>> data;
	parseFile(argc, argv, data);
	printFractals(data);


	return 0;
}