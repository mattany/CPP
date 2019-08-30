//
// Created by mattan on 8/27/19.
//

#include <cassert>
#include "GFNumber.h"
#include <random>
#include <cmath>

long *GFNumber::getPrimeFactors(size_t& size) const //todo
{
    long n = _n;
    assert(size == 1);  //todo Delete
    long* factors = new long[size];
    while (pollardRho(n, factors, size))
    {
        n /= factors[-1];
    }
    naiveSearch(n, factors, size);
    return factors;
}

bool GFNumber::pollardRho(long number, long* (&factors), size_t & size) const
{
    if (number == 1) return false;
    GFNumber x(rng(number),_gField), y, p(1, _gField), n(number, _gField);
    while (p.getNumber() == 1)
    {
        x = f(x);
        y = f(f(x));
        p = _gField.gcd(GFNumber(labs(x._n-y._n), _gField), n);
    }
    if (p != n)
    {
        append(p._n, factors, size);
        return true;
    }
    return false;
}

void GFNumber::naiveSearch(long n, long* (&factors), size_t & size) const
{
    long i = 2;
    while (i < sqrt(n))
    {
        if (n % i == 0)
        {
            append(i, factors, size);
            n /= i;
        }
        else
        {
            i += 1;
        }
    }
    if (n > 1)
    {
        append(n, factors, size);
    }
}

void GFNumber::append(long val, long *&array, size_t &size) const
{
    size_t newSize = size + 1;
    long * ret = new long[newSize];
    std::copy(array, array + size, ret);
    delete[] array;
    array = ret;
    assert(array[-1] == 0);   //TODO delete
    array[-1] = val;
    size = newSize;
}

long GFNumber::rng(long n) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1,n - 1);

    return distribution(rng);
}

void GFNumber::printFactors() const
{
    size_t size = 1;
    long* factors = getPrimeFactors(size);
    std::cout << _n;
    if (size != 1)
    {
        std::cout << "=";
        for (size_t i = 0; i < size; i++)
        {
            std::cout << factors[i] << "*";
        }
    }
    std::cout << std::endl;
}

GFNumber &GFNumber::operator=(const GFNumber &other)
{
    _n = other._n;
    _gField = other._gField;
    return *this;
}

GFNumber GFNumber::operator+(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n + other._n), _gField);
}

GFNumber &GFNumber::operator+=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n + other._n);
    return *this;
}

GFNumber GFNumber::operator-(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n - other._n), _gField);
}

GFNumber &GFNumber::operator-=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n - other._n);
    return *this;
}

GFNumber GFNumber::operator*(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(modulo(_n * other._n), _gField);
}

GFNumber &GFNumber::operator*=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n = modulo(_n * other._n);
    return *this;
}

GFNumber GFNumber::operator%(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return GFNumber(_n % other._n, _gField);
}

GFNumber &GFNumber::operator%=(const GFNumber &other)
{
    assert(_gField == other._gField);
    _n %= other._n;
    return *this;
}

GFNumber &GFNumber::operator=(long n)
{
    _n = modulo(n);
    return *this;
}

GFNumber GFNumber::operator+(long n) const
{ return GFNumber(modulo(_n + n), _gField); }

GFNumber &GFNumber::operator+=(long n)
{
    _n = modulo(_n + n);
    return *this;
}

GFNumber GFNumber::operator-(long n) const
{ return GFNumber(modulo(_n - n), _gField); }

GFNumber &GFNumber::operator-=(long n)
{
    _n = modulo(_n - n);
    return *this;
}

GFNumber GFNumber::operator*(long n) const
{ return GFNumber(modulo(_n * n), _gField); }

GFNumber &GFNumber::operator*=(long n)
{
    _n = modulo(_n * n);
    return *this;
}

GFNumber GFNumber::operator%(long n) const
{ return GFNumber(modulo(_n % n), _gField); }

GFNumber &GFNumber::operator%=(long n)
{
    _n = modulo(_n % n);
    return *this;
}

bool GFNumber::operator==(const GFNumber &other) const
{
    return (_n == other._n && _gField == other._gField);
}

bool GFNumber::operator!=(const GFNumber &other) const
{
    return (_n != other._n || _gField != other._gField);
}

bool GFNumber::operator<=(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n <= other._n);
}

bool GFNumber::operator>=(const GFNumber &other) const
{
    assert(_gField == other._gField);
    return (_n >= other._n);
}

std::ostream &operator<<(std::ostream &out, const GFNumber &gfNumber)
{
	out << gfNumber._n << " " << gfNumber._gField;
	return out;
}

std::istream &operator>>(std::istream &in, GFNumber &gfNumber)
{
	long n; GField gField;
	in >> n >> gField;
    gfNumber._gField = gField;
    gfNumber._n = gfNumber.modulo(n);
	return in;
}



