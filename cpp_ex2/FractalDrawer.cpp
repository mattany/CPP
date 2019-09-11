#include <iostream>
#include <fstream>
#include <regex>
#include "Fractal.h"

enum FractalTypes
	{
	CARPET = 1,
	SIEVE,
	CANTOR
	};
static const int FRACTAL_TYPE = 0;
static const int FRACTAL_DIMENSION = 2;
static const int MAX_FRACTAL_DIMENSION = 6;
static const int MAX_FRACTAL_TYPE = 3;
static const int MAX_LINE_LENGTH = 3;
static const int DELIMITER = 1;
static const int MIN_FRACTAL_TYPE = 1;
static const int MIN_FRACTAL_DIMENSION = 1;
static const int CORRECT_ARG_NUMBER = 2;
static const int FILE_PATH = 1;
static const int FRACTAL_DIM = 1;
static const char* INPUT = "Invalid input";
static const char* USAGE = "Usage: FractalDrawer <file path>";

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
    return (line.length() == MAX_LINE_LENGTH &&
            line[DELIMITER] == ',' &&
            isdigit(line[FRACTAL_TYPE]) &&
            isdigit(line[FRACTAL_DIMENSION]) &&
            MIN_FRACTAL_TYPE <= (line[FRACTAL_TYPE]) - '0' &&
            line[FRACTAL_TYPE] - '0' <= MAX_FRACTAL_TYPE &&
            MIN_FRACTAL_DIMENSION <= line[FRACTAL_DIMENSION] - '0' &&
            line[FRACTAL_DIMENSION] - '0' <= MAX_FRACTAL_DIMENSION);
}

/**
 * @param argc arg count
 * @param argv arguments
 * @param data pairs of (type, dimension)
 */
bool parseFile(int argc, char *const *argv, std::stack<std::pair<int, int>> &data)
{
    if (argc != CORRECT_ARG_NUMBER)
    {
	    usageError();
	    return false;
    }
    std::ifstream infile;
    infile.open(argv[FILE_PATH]);
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
        data.push(std::make_pair(line[FRACTAL_TYPE] - '0', line[FRACTAL_DIMENSION] - '0'));
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
        type = std::get<FRACTAL_TYPE>(data.top());
        dim = std::get<FRACTAL_DIM>(data.top());
        switch (type)
        {
            case CARPET:
            {
                auto carpet = Carpet(dim);
                carpet.print();
                break;
            }
            case SIEVE:
            {
                auto sieve = Sieve(dim);
                sieve.print();
                break;
            }
            case CANTOR:
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