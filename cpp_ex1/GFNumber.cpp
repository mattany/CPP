//
// Created by mattan on 8/27/19.
//

#include <assert.h>
#include "GFNumber.h"

long *GFNumber::getPrimeFactors() const //todo
{ return 0; }

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

