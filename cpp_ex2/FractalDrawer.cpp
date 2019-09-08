#include <iostream>
#include <fstream>
#include <regex>
#include "Fractal.h"

#define INPUT "Invalid input"
#define USAGE "Usage: FractalDrawer <file path>"

/**
 * @return exit failure
 */
void usageError()
{
    std::cerr << USAGE << std::endl;
}

/**
 * @return exit failure
 */
void inputError()
{
    std::cerr << INPUT << std::endl;

}

/**
 * @param line
 * @return true if line is in correct format
 */
bool goodInput(const std::string &line)
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

/**
 * @param argc arg count
 * @param argv arguments
 * @param data pairs of (type, dimension)
 */
bool parseFile(int argc, char *const *argv, std::stack<std::pair<int, int>> &data)
{
    if (argc != 2)
    {
	    usageError();
	    return false;
    }
    std::ifstream infile;
    infile.open(argv[1]);
    if (!infile)
    {
	    inputError();
	    return false;
    }
    std::string line;
    while (getline(infile, line))
    {
        if (!goodInput(line))
        {
	        inputError();
	        return false;
        }
        data.push(std::make_pair(line[0] - '0', line[2] - '0'));
    }
    infile.clear();
    return true;
}

/**
 * print the fractals
 */
void printFractals(std::stack<std::pair<int, int>> &data)
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

/**
 * the main function
 * @param argc arg count
 * @param argv arguments
 */
int main(int argc, char **argv)
{
    std::stack<std::pair<int, int>> data;
    if (!parseFile(argc, argv, data))
    {
    	return EXIT_FAILURE;
    }
    printFractals(data);
    return 0;
}