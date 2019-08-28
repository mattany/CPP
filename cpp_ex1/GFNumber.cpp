//
// Created by mattan on 8/27/19.
//

#include <assert.h>
#include "GFNumber.h"

long *GFNumber::getPrimeFactors() const //todo
{ return 0;}

std::string GFNumber::printFactors() const
{ return 0;}

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
	return GFNumber((_n * other._n) % _gField.getOrder(), _gField);
}

GFNumber &GFNumber::operator*=(const GFNumber &other)
{
	assert(_gField == other._gField);
	_n = (_n * other._n) % _gField.getOrder();
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

GFNumber &GFNumber::operator=(const long other)
{

	_n = (other >= 0) ? (other % _gField.getChar()) : ();
	return *this;
}

GFNumber GFNumber::operator+(const long other) const
{}

GFNumber &GFNumber::operator+=(long other)
{}

GFNumber GFNumber::operator-(long other) const
{}

GFNumber &GFNumber::operator-=(long other)
{}

GFNumber GFNumber::operator*(long other) const
{}

GFNumber &GFNumber::operator*=(long other)
{}

GFNumber GFNumber::operator%(long other) const
{}

GFNumber &GFNumber::operator%=(long other)
{}

bool GFNumber::operator==(const GFNumber &other) const
{}

bool GFNumber::operator!=(const GFNumber &other) const
{}

bool GFNumber::operator<=(const GFNumber &other) const
{}

bool GFNumber::operator>=(const GFNumber &other) const
{}
