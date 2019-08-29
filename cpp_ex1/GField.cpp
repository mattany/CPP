//
// Created by mattan on 8/27/19.
//


#include <cassert>
#include "GField.h"
#include "GFNumber.h"

bool GField::isPrime(long p)
{
	double root = sqrt(p);
	for (long i = 2; i <= root; i++)
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

std::ostream &operator<<(std::ostream &out, const GField &gField)
{
	out << "GF(" << gField._p << "**" << gField._l << ")";
	return out;
}

std::istream &operator>>(std::istream &in, GField &gField)
{
	long p, l;
	in >> p >> l;
    assert(gField.isPrime(p) && l >= 0);
	gField._p = p;
	gField._l = l;
	return in;
}


GFNumber GField::gcd(const GFNumber& num1, const GFNumber& num2) const
{
	assert(num1.getField() == num2.getField());
	long a = num1.getNumber(), b = num2.getNumber();
	while (b != 0)
	{
		long temp = b;
		b = a % b;
		a = temp;
	}
	return GFNumber(b);

}

GFNumber GField::createNumber(long k) const
{return GFNumber(k, *this);}
