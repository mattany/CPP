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
	GFNumber(long n, const GField &gField) : _gField(gField)
	{
		_n = modulo(n);
	}

	long modulo(long n) const
	{ return (n >= 0) ? (n % _gField.getOrder()) : (n % _gField.getOrder() + _gField.getOrder());}

	GFNumber() : GFNumber(0, GField())
	{}

	explicit GFNumber(long n) : GFNumber(n, GField())
	{}

	GFNumber(const GFNumber &other): GFNumber(other._n, other._gField) {}

	~GFNumber() {}

	long getNumber() const { return _n; }

	const GField &getField() const { return _gField; }

	GFNumber * getPrimeFactors(size_t &size) const;

	void printFactors() const;

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

	friend std::ostream &operator<<(std::ostream& out, const GFNumber& gfNumber);

	friend std::istream &operator>>(std::istream& in, GFNumber& gfNumber);

	bool pollardRho(long& number, long* (&factors), size_t & size) const; //TODO make private

	void naiveSearch(long n, long* (&factors), size_t& size) const;  //TODO make private
private:
	long _n;
	GField _gField;

	long rng(long n) const;

	inline GFNumber f(const GFNumber&  n) const
    { return GFNumber(n._n * n._n + 1, n._gField);}

    void append(long val, long *&array, size_t &size) const;

};


#endif //CPP_EX1_GFNUMBER_H
