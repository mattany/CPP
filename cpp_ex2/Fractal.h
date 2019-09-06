
//
// Created by mattan on 9/4/19.
//

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

using std::vector;

class Fractal
{
public:
    explicit Fractal(int dimension, int height, int width) :
            _dim(dimension), _height(height), _width(width)
    {}

    void print()
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

protected:

    virtual void setPattern() = 0;

    void setMatrix()
    {
        int rows = (int) pow(_height, _dim);
        int cols = (int) pow(_width, _dim);
        _matrix.resize(rows, vector<bool>(cols, false));
        populateMatrix(_dim, 0, 0, _matrix);
    }

    void populateMatrix(int dim, int i, int j, vector<vector<bool>> &matrix)
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

    const int _dim;
    const int _height;
    const int _width;
    vector<vector<bool>> _pattern;
    vector<vector<bool>> _matrix;
};

class Cantor : public Fractal
{
public:
    Cantor(int dimension):
    Fractal(dimension, 3, 3)
    {
        setPattern();
        setMatrix();
    }
private:
    void setPattern() override
    {
        vector<bool> vec1 = {true,false,true};
        vector<bool> vec2(3,false);
        _pattern = {vec1, vec2, vec1};
    }
};

class Sierpinski : public Fractal
{

public:
    Sierpinski(int dimension, int height, int width) :
            Fractal(dimension, height, width)
    {
        setPattern();
        setMatrix();
    }

protected:
    void setPattern() override
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
};

class Carpet : public Sierpinski
{
public:
    Carpet(int dimension):
    Sierpinski(dimension, 3,3){}
};

class Sieve : public Sierpinski
{
public:
    Sieve(int dimension):
    Sierpinski(dimension, 2,2){}
};





#endif //CPP_EX2_FRACTAL_H
