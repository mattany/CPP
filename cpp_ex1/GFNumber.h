//
// Created by mattan on 8/27/19.
//

#ifndef CPP_EX1_GFNUMBER_H
#define CPP_EX1_GFNUMBER_H

#include <string>
#include "GField.h"

class GFNumber
{
public:
	GFNumber(long n, const GField &gField) : _n(n), _gField(gField)
	{}

	GFNumber() : GFNumber(0, GField())
	{}

	explicit GFNumber(long n) : GFNumber(n, GField())
	{}

	GFNumber(const GFNumber &other): GFNumber(other._n, other._gField) {}

	~GFNumber() {}

	long getNumber() const
	{ return _n; }

	const GField &getField() const
	{ return _gField; }

	long *getPrimeFactors() const;

	std::string printFactors() const;

	bool getIsPrime() const
	{ return GField::isPrime(_n); }

	GFNumber &operator=(const GFNumber &other);

	GFNumber operator+(const GFNumber &other) const;

	GFNumber &operator+=(const GFNumber &other);

	GFNumber operator-(const GFNumber &other) const;

	GFNumber &operator-=(const GFNumber &other);

	GFNumber operator*(const GFNumber &other) const;

	GFNumber &operator*=(const GFNumber &other);

	GFNumber operator%(const GFNumber &other) const;

	GFNumber &operator%=(const GFNumber &other);

	GFNumber &operator=(long other);

	GFNumber operator+(long other) const;

	GFNumber &operator+=(long other);

	GFNumber operator-(long other) const;

	GFNumber &operator-=(long other);

	GFNumber operator*(long other) const;

	GFNumber &operator*=(long other);

	GFNumber operator%(long other) const;

	GFNumber &operator%=(long other);

	bool operator==(const GFNumber &other) const;

	bool operator!=(const GFNumber &other) const;

	bool operator<=(const GFNumber &other) const;

	bool operator>=(const GFNumber &other) const;


private:
	long _n;
	GField _gField;
};


#endif //CPP_EX1_GFNUMBER_H
