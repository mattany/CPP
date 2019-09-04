
//
// Created by mattan on 9/4/19.
//

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H
#include <vector>

class Fractal
{
	Fractal(int height, int width, int mult):
	_mult = mult, _pattern = pattern;

	enum pattern = {carpet = 1, sieve, dust};
private:
	std::vector<std::vector<bool>>;
	std::vector<std::vector<bool>> matrix;
	const int _height, _width, _mult;


};
#endif //CPP_EX2_FRACTAL_H
