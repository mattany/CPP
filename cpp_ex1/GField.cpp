//
// Created by mattan on 8/27/19.
//


#include "GField.h"

bool GField::isPrime(long p)
{
	long root = (long) ceil(sqrt(p));
	for (long i = 0; i < root; i++)
	{
		if (p % i == 0)
		{
			return false;
		}
	}
	return true;
}

long GField::getOrder() const
{
	long ret = 1;
	for (long i = 0; i < _l; i++)
	{
		ret *= _p;
	}
	return ret;
}

GField &GField::operator=(const GField &other)
{
	_p = other._p;
	_l = other._l;
	return *this;
}