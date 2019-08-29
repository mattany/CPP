//
// Created by mattan on 8/27/19.
//

#ifndef CPP_EX1_GFIELD_H
#define CPP_EX1_GFIELD_H

#include <cmath>
#include <cassert>
#include <iostream>

class GFNumber;

class GField
{
public:
	explicit GField(long p, long l): _p(p), _l(l) {assert (isPrime(p) && l > 0);}

	GField(): GField(2, 1) {}

	GField(GField const &gField): GField(gField._p, gField._l) {}

	~GField(){}

	long getChar() const
	{ return _p; }

	long getDegree() const
	{ return _l; }


	long getOrder() const;

	static bool isPrime(long p);

	GFNumber gcd(const GFNumber& num1, const GFNumber& num2) const;

	GFNumber createNumber(long k) const;

	GField & operator=(const GField &other);

	bool operator==(const GField &other) const {return _p == other._p && _l == other._l;}

	bool operator!=(const GField &other) const {return _p != other._p || _l != other._l;}

	friend std::ostream& operator<<(std::ostream& out, const GField& gField);

	friend std::istream& operator>>(std::istream& in, GField& gField);
private:
	long _p;
	long _l;
};


#endif //CPP_EX1_GFIELD_H
