
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

    void print() const;

protected:
    virtual void setPattern() = 0;

    void setMatrix();

    void populateMatrix(int dim, int i, int j, vector<vector<bool>> &matrix);

    const int _dim;
    const int _height;
    const int _width;
    vector<vector<bool>> _pattern;
    vector<vector<bool>> _matrix;
};

class Cantor : public Fractal
{
public:
    explicit Cantor(int dimension);

private:
    void setPattern() override;
};

class Sierpinski : public Fractal
{

public:
    Sierpinski(int dimension, int height, int width);

protected:
    void setPattern() override;
};

class Carpet : public Sierpinski
{
public:
    explicit Carpet(int dimension);
};

class Sieve : public Sierpinski
{
public:
    explicit Sieve(int dimension);
};


#endif //CPP_EX2_FRACTAL_H
