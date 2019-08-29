//
// Created by mattan on 8/27/19.
//

#include <cassert>
#include "GFNumber.h"
#include <random>
#include <cmath>
long *GFNumber::getPrimeFactors() const //todo
{
    long n = _n;
    long* primes = new long[1];
    while (n != 1)
    {
        if (pollardRho(n) == -1)
        {

        }
    }
    return 0;
}

long GFNumber::pollardRho(long number) const
{
    GFNumber x(rng(number),_gField), y, p(1, _gField), n(number, _gField);
    while (p.getNumber() == 1)
    {
        x = f(x);
        y = f(f(x));
        p = _gField.gcd(GFNumber(labs(x._n-y._n), _gField), n);
    }
    return (p == n) ? -1 : p._n;
}

long GFNumber::rng(long n)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1,n - 1);

    return distribution(rng);
}

std::string GFNumber::printFactors() const
{ return 0; }

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


