//
// Created by mattan on 8/27/19.
//

#ifndef CPP_EX1_GFIELD_H
#define CPP_EX1_GFIELD_H

#include <cmath>
#include "GFNumber.h"
#include <iostream>

class GField
{
public:
	GField() :
			_p(2), _l(1)
	{}

	explicit GField(long p, long l) :
			_p(p), _l(l)
	{}

	GField(GField const &gField)
	= default;

	~GField()
	= default;

	long getChar() const
	{ return _p; }

	long getDegree() const
	{ return _l; }


	long getOrder() const;

	static bool isPrime(long p);

	GFNumber gcd(GFNumber a, GFNumber b)  //TODO
	{return a;}

	GFNumber createNumber(long k) const
	{return GFNumber(k, &this)}

	GField & operator=(const GField &other);

	bool operator==(GField &other) {return _p == other._p && _l == other._l}

	bool operator!=(GField &other) {return _p != other._p || _l != other._l}

	friend std::ostream& operator>>(){}
private:
	long _p;
	long _l;
};


#endif //CPP_EX1_GFIELD_H
