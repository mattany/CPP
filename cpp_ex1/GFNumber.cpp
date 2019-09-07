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
GFNumber *GFNumber::getPrimeFactors(int *size) const
{
    *size = 0;
    long n = _n;
    if (_n == 0 || _n == 1 || _n == 2)   // Should not enter this if called from PrintFactors
    {
        return new GFNumber[*size];
    }
    long *temp = new long[*size]();
    _halve(n, temp, size);
    if (GField::isPrime(n))
    {
        *size = 0;
        n = 1;   // Terminate quickly
    }
    while (_pollardRho(n, temp, size))
    {
        n /= temp[*size - 1];
    }
    _naiveSearch(n, temp, size);
    auto *factors = new GFNumber[*size];
    for (int i = 0; i < *size; i++)
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
    if (_n == 1 || _n == 0)
    {
        std::cout << _n << "=" << _n << "*" << 1 << std::endl;
        return;
    }
    int size = 0;
    GFNumber *factors = getPrimeFactors(&size);
    std::cout << _n;
    std::cout << "=";
    for (int i = 0; i < size - 1; i++)
    {
        std::cout << factors[i]._n << "*";
    }
    if (size > 0)
    {
        std::cout << factors[size - 1]._n;
    }
    else
    {
        std::cout << _n << "*" << "1";
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
    return GFNumber(_modulo(_n + other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator+=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = _modulo(_n + other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator-(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(_modulo(_n - other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator-=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = _modulo(_n - other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator*(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(_modulo(_n * other._n), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator*=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = _modulo(_n * other._n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator%(const GFNumber &other) const
{
    assert(_gField == other._gField && other._n != 0);
    return GFNumber(_n % other._n, _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator%=(const GFNumber &other)
{
    assert(_gField == other._gField && other._n != 0);
    _n %= other._n;
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator+(long n) const
{ return GFNumber(_modulo(_n + n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator+=(long n)
{
    _n = _modulo(_n + n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator-(long n) const
{ return GFNumber(_modulo(_n - n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator-=(long n)
{
    _n = _modulo(_n - n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator*(long n) const
{ return GFNumber(_modulo(_n * n), _gField); }

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator*=(long n)
{
    _n = _modulo(_n * n);
    return *this;
}

/**
 * @param other
 * @return result
 */
GFNumber GFNumber::operator%(long n) const
{
    assert(n != 0);
    return GFNumber(_modulo(_n % _modulo(n)), _gField);
}

/**
 * @param other
 * @return result
 */
GFNumber &GFNumber::operator%=(long n)
{
    assert(n != 0);
    _n = _modulo(_n % _modulo(n));
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
    return !(*this == (other));
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
    long n;
    GField gField;
    in >> n >> gField;
    assert(!in.fail());
    gfNumber._gField = gField;
    gfNumber._n = gfNumber._modulo(n);
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
long GFNumber::_rng(long n) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, n - 1);

    return distribution(rng);
}

/**
 * appends the value to the array.
 * @param val value to add
 * @param array reference to an array
 * @param size old size of array
 */
void GFNumber::_append(long val, long *&array, int *size) const
{
    int newSize = *size + 1;
    long *ret = new long[newSize]();
    std::copy(array, array + *size, ret);
    delete[] array;
    array = ret;
    array[newSize - 1] = val;
    *size = newSize;
}

/**
 * @param number
 * @param factors array
 * @param size of array
 * @return true iff succeeded in finding factors.
 */
bool GFNumber::_pollardRho(long &number, long *(&factors), int *size) const
{
    if (number == 1)
    {
        return false;
    }
    GFNumber x(_rng(number), _gField), y = x, p(1, _gField), n(number, _gField);
    while (p.getNumber() == 1)
    {
        x = _f(x);
        y = _f(_f(y));
        p = _gField.gcd(GFNumber(labs(x._n - y._n), _gField), n);
    }
    if (p != n)
    {
        if (GField::isPrime(p._n))
        {
            _append(p._n, factors, size);
            return true;
        }
        _naiveSearch(p._n, factors, size);   //Else do brute force on the factor
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
void GFNumber::_naiveSearch(long n, long *(&factors), int *size) const
{
    long i = 2;
    long root = (long) sqrt((double) n);
    while (i <= root)
    {
        if (n % i == 0)
        {
            _append(i, factors, size);
            n /= i;
        }
        else
        {
            i += 1;
        }
    }
    if (n > 1)
    {
        _append(n, factors, size);
    }
}

/**
 * divide by 2 and append factors array while even
 * @param number number
 * @param factors array
 * @param size of array
 */
void GFNumber::_halve(long &number, long *&factors, int *size) const
{
    while (number % 2 == 0)
    {
        number /= 2;
        _append(2, factors, size);
    }
}

