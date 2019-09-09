//
// Created by mattan on 9/4/19.
//

#include "Fractal.h"

/**
     * print the fractal
     */
void Fractal::print() const
{
	for (const vector<bool> &row : _matrix)
	{
		for (bool bit : row)
		{
			(bit) ? std::cout << "#" : std::cout << " ";
		}
		std::cout << std::endl;
	}
}

/**
 * set the fractal matrix with the correct values
 */
void Fractal::setMatrix()
{
	int rows = (int) pow(_height, _dim);
	int cols = (int) pow(_width, _dim);
	_matrix.resize(rows, vector<bool>(cols, false));
	populateMatrix(_dim, FIRST_ROW, FIRST_COL, _matrix);
}

/**
 * Fill matrix recursively according to the pattern
 * @param dim dimension
 * @param i row
 * @param j column
 * @param matrix input matrix
 */
void Fractal::populateMatrix(int dim, int i, int j, vector<vector<bool>> &matrix)
{
	dim = dim - 1;
	int pixel_height = (int) pow(_height, dim);
	int _pixel_width = (int) pow(_width, dim);
	for (int k = 0; k < _height; k++)
	{
		for (int l = 0; l < _width; l++)
		{
			if (_pattern[k][l])
			{
				if (dim == 0)
				{
					matrix[i + k * pixel_height][j + l * _pixel_width] = true;
				}
				else
				{
					populateMatrix(dim, i + k * pixel_height, j + l * _pixel_width, matrix);
				}
			}
		}
	}
}

/**
 * ctor
 * @param dimension
 */
Cantor::Cantor(int dimension) :
		Fractal(dimension, 3, 3)
{
	setPattern();
	setMatrix();
}

/**
 * set the pattern
 */
void Cantor::setPattern()
{
	vector<bool> vec1 = {true, false, true};
	vector<bool> vec2(3, false);
	_pattern = {vec1, vec2, vec1};
}

/**
 * @param dimension
 * @param height
 * @param width
 */
Sierpinski::Sierpinski(int dimension, int height, int width) :
		Fractal(dimension, height, width)
{
	setPattern();
	setMatrix();
}

/**
 * set the pattern
 */
void Sierpinski::setPattern()
{
	_pattern.resize((size_t) _height, vector<bool>((size_t) _width, false));
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			_pattern[i][j] = true;
		}
		_pattern[1][1] = false;
	}
}

/**
 * ctor
 * @param dimension
 */
Carpet::Carpet(int dimension) :
		Sierpinski(dimension, 3, 3)
{}

/**
 * ctor
 * @param dimension
 */
Sieve::Sieve(int dimension) :
		Sierpinski(dimension, 2, 2)
{}
