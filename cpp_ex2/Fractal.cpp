//
// Created by mattan on 9/4/19.
//

#include "Fractal.h"

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

void Fractal::setMatrix()
{
    int rows = (int) pow(_height, _dim);
    int cols = (int) pow(_width, _dim);
    _matrix.resize(rows, vector<bool>(cols, false));
    populateMatrix(_dim, 0, 0, _matrix);
}

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
                } else
                {
                    populateMatrix(dim, i + k * pixel_height, j + l * _pixel_width, matrix);
                }
            }
        }
    }
}

Cantor::Cantor(int dimension) :
        Fractal(dimension, 3, 3)
{
    setPattern();
    setMatrix();
}

void Cantor::setPattern()
{
    vector<bool> vec1 = {true,false,true};
    vector<bool> vec2(3,false);
    _pattern = {vec1, vec2, vec1};
}

Sierpinski::Sierpinski(int dimension, int height, int width) :
        Fractal(dimension, height, width)
{
    setPattern();
    setMatrix();
}

void Sierpinski::setPattern()
{
    _pattern.resize(_height, vector<bool>(_width, false));
    for (int i = 0; i < _height; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            _pattern[i][j] = true;
        }
        _pattern[1][1] = false;
    }
}

Carpet::Carpet(int dimension) :
        Sierpinski(dimension, 3,3){}

Sieve::Sieve(int dimension) :
        Sierpinski(dimension, 2,2){}
