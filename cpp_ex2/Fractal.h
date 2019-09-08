
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

/**
 * Fractal Class
 */
class Fractal
{
public:
	/**
	 * Initialize fields
	 * @param dimension
	 * @param height
	 * @param width
	 */
	explicit Fractal(int dimension, int height, int width) :
			_dim(dimension), _height(height), _width(width)
	{}

	/**
	 * print the fractal
	 */
	void print() const;

protected:
	/**
	 * set the pattern field to the fractal pattern
	 */
	virtual void setPattern() = 0;

	/**
	 * set the fractal matrix with the correct values
	 */
	void setMatrix();

	/**
	 * Fill matrix recursively according to the pattern
	 * @param dim dimension
	 * @param i row
	 * @param j column
	 * @param matrix input matrix
	 */
	void populateMatrix(int dim, int i, int j, vector<vector<bool>> &matrix);

	const int _dim;                  /** dimension */
	const int _height;               /** height */
	const int _width;                /** width */
	vector<vector<bool>> _pattern;    /** pattern (fractal with dim 1) */
	vector<vector<bool>> _matrix;     /** matrix representation of fractal */
};

/**
 * Cantor Dust Fractal
 */
class Cantor : public Fractal
{
public:
	/**
	 * ctor
	 * @param dimension
	 */
	explicit Cantor(int dimension);

	/**
	 * copy ctor
	 * @param other
	 */
	Cantor(const Cantor &other) = default;

	/**
	 * copy assignment operator
	 * @param other
	 * @return
	 */
	Cantor &operator = (const Cantor &other) = default;

	/**
	 * move ctor
	 * @param other
	 */
	Cantor(Cantor && other) noexcept = default;

	/**
	 * move assignment operator
	 * @param other
	 * @return
	 */
	Cantor &operator = (Cantor && other) noexcept = default;

	/**
	 * dtor
	 */
	~Cantor() = default;


private:
	/**
	 * set the pattern
	 */
	void setPattern() override;
};

/**
 * Sierpinski Carpet
 */
class Sierpinski : public Fractal
{

public:
	/**
	 * @param dimension
	 * @param height
	 * @param width
	 */
	Sierpinski(int dimension, int height, int width);

protected:
	/**
	 * set the pattern
	 */
	void setPattern() override;
};

/**
 * Sierpinski Carpet
 */
class Carpet : public Sierpinski
{
public:

	/**
	 * ctor
	 * @param dimension
	 */
	explicit Carpet(int dimension);

	/**
	 * copy ctor
	 * @param other
	 */
	Carpet(const Carpet &other) = default;

	/**
	 * copy assignment operator
	 * @param other
	 * @return
	 */
	Carpet &operator = (const Carpet &other) = default;

	/**
	 * move ctor
	 * @param other
	 */
	Carpet(Carpet && other) noexcept = default;

	/**
	 * move assignment operator
	 * @param other
	 * @return
	 */
	Carpet &operator = (Carpet && other) noexcept = default;

	/**
	 * dtor
	 */
	~Carpet() = default;
};

/**
 * Sierpinski Sieve
 */
class Sieve : public Sierpinski
{
public:
	/**
	 * ctor
	 * @param dimension
	 */
	explicit Sieve(int dimension);

	/**
	 * copy ctor
	 * @param other
	 */
	Sieve(const Sieve &other) = default;

	/**
	 * copy assignment operator
	 * @param other
	 * @return
	 */
	Sieve &operator = (const Sieve &other) = default;

	/**
	 * move ctor
	 * @param other
	 */
	Sieve(Sieve && other) noexcept = default;

	/**
	 * move assignment operator
	 * @param other
	 * @return
	 */
	Sieve &operator = (Sieve && other) noexcept = default;

	/**
	 * dtor
	 */
	~Sieve() = default;
};


#endif //CPP_EX2_FRACTAL_H
