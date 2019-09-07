#include <iostream>
#include <fstream>
#include <regex>
#include "Fractal.h"

#define INPUT "Invalid input"
#define USAGE "Usage: FractalDrawer <file path>"

/**
 * @return exit failure
 */
int usage_error()
{
    std::cerr << USAGE << std::endl;
    exit(EXIT_FAILURE);
}

/**
 * @return exit failure
 */
int input_error()
{
    std::cerr << INPUT << std::endl;
    exit(EXIT_FAILURE);
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
void parseFile(int argc, char *const *argv, std::stack<std::pair<int, int>> &data)
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
    parseFile(argc, argv, data);
    printFractals(data);
    return 0;
}