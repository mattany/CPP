//
// Created by mattan on 8/27/19.
//

#include <cassert>
#include "GFNumber.h"
#include <random>
#include <cmath>

/*****************************************************************************************
                                        Getters
******************************************************************************************/

/**
     * @param size reference to size of array
     * @return array of factors
     */
GFNumber * GFNumber::getPrimeFactors(size_t &size) const
{
    long n = _n;
    long* temp = new long[size]();
    while (pollardRho(n, temp, size))
    {
        n /= temp[size - 1];
    }
    naiveSearch(n, temp, size);
    auto* factors = new GFNumber[size];
    for (size_t i = 0; i < size; i++)
    {
        factors[i] = GFNumber(temp[i], _gField);
    }
    delete[] temp;
    return factors;
}

/**
     * print formatted factors
     */
void GFNumber::printFactors() const
{
    size_t size = 0;
    GFNumber* factors = getPrimeFactors(size);
    std::cout << _n;
	std::cout << "=";
    for (size_t i = 0; i < size - 1; i++)
    {
        std::cout << factors[i]._n << "*";
    }
    std::cout << factors[size - 1]._n;
    if (size == 1)
    {
	    std::cout << "*" << "1";
    }
    std::cout << std::endl;
    delete[] factors;
}

/*****************************************************************************************
                                       operators
******************************************************************************************/

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator+(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n + other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator+=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n + other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator-(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n - other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator-=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n - other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator*(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n * other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator*=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n * other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator%(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(_n % other._n, _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator%=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n %= other._n;
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator+(long n) const
{ return GFNumber(modulo(_n + n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator+=(long n)
{
    _n = modulo(_n + n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator-(long n) const
{ return GFNumber(modulo(_n - n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator-=(long n)
{
    _n = modulo(_n - n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator*(long n) const
{ return GFNumber(modulo(_n * n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator*=(long n)
{
    _n = modulo(_n * n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator%(long n) const
{
    return GFNumber(modulo(_n % modulo(n)), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator%=(long n)
{
    _n = modulo(_n % modulo(n));
    return *this;
}

/**
 * @param other
 * @return true iff this == other
 */
bool GFNumber::operator==(const GFNumber &other) const
{
    return (_n == other._n && _gField.getOrder() == other._gField.getOrder());
}

/**
 * @param other
 * @return true iff this != other
 */
bool GFNumber::operator!=(const GFNumber &other) const
{
    return !(*this==(other));
}

/**
 * @param other
 * @return true iff this <= other
 */
bool GFNumber::operator<=(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n <= other._n);
}

/**
 * @param other
 * @return true iff this >= other
 */
bool GFNumber::operator>=(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n >= other._n);
}

/**
 * @param out output stream
 * @param gfNumber
 * @return reference to output stream after printing gfNumber
 */
std::ostream &operator<<(std::ostream &out, const GFNumber &gfNumber)
{
	out << gfNumber._n << " " << gfNumber._gField;
	return out;
}

/**
 * @param in input stream
 * @param gfNumber
 * @return reference to input stream after assigning values to gfNumber
 */
std::istream &operator>>(std::istream &in, GFNumber &gfNumber)
{
	long n; GField gField;
	in >> n >> gField;
    gfNumber._gField = gField;
    gfNumber._n = gfNumber.modulo(n);
	return in;
}

/**
 * @param other
 * @return true iff this > other
 */
bool GFNumber::operator>(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n > other._n);
}

/**
 * @param other
 * @return true iff this < other
 */
bool GFNumber::operator<(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n < other._n);
}

/*****************************************************************************************
                                     private methods
******************************************************************************************/

/**
 * @param n
 * @return random number between 1 and n-1
 */
long GFNumber::rng(long n) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1,n - 1);

    return distribution(rng);
}

/**
 * appends the value to the array.
 * @param val value to add
 * @param array reference to an array
 * @param size old size of array
 */
void GFNumber::append(long val, long *&array, size_t &size) const
{
    size_t newSize = size + 1;
    long * ret = new long[newSize]();

    std::copy(array, array + size, ret);
    delete[] array;
    array = ret;
    array[newSize - 1] = val;
    size = newSize;
}

/**
 * @param number
 * @param factors array
 * @param size of array
 * @return true iff succeeded in finding factors.
 */
bool GFNumber::pollardRho(long& number, long* (&factors), size_t & size) const
{
    halve(number, factors, size);
    if (number == 1) return false;
    GFNumber x(rng(number),_gField), y = x, p(1, _gField), n(number, _gField);
    while (p.getNumber() == 1)
    {
        x = f(x);
        y = f(f(y));
        p = _gField.gcd(GFNumber(labs(x._n-y._n), _gField), n);
    }
    if (p != n)
    {
        if (GField::isPrime(p._n))
        {
            append(p._n, factors, size);
            return true;
        }
        naiveSearch(p._n, factors, size);   //Else do brute force on the factor
        number /= p._n;
    }
    return false;
}

/**
 * put the prime factors comprising n in factors array
 * @param n number
 * @param factors array
 * @param size of array
 */
void GFNumber::naiveSearch(long n, long* (&factors), size_t & size) const
{
    long i = 2;
    if (n == 1)
    {
        append(n, factors, size);
        return;
    }
    long root = floor(sqrt((double)n));
    while (i <= root)
    {
        if (n % i == 0)
        {
            append(i, factors, size);
            n /= i;
        }
        else i += 1;

    }
    if (n > 1)
    {
        append(n, factors, size);
    }
}

/**
 * divide by 2 and append factors array while even
 * @param number number
 * @param factors array
 * @param size of array
 */
void GFNumber::halve(long &number, long *&factors, size_t &size) const
{
    while (number % 2 == 0)
    {
        number /= 2;
        append(2, factors, size);
    }
}

