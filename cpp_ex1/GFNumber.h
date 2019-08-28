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
	GFNumber(long n, const GField& gField): _n(n), _gField(gField){}

	GFNumber(): GFNumber(0, GField()) {}

	explicit GFNumber(long n): GFNumber(n, GField()) {}

	GFNumber(const GFNumber& other);

	~GFNumber() {}

	long getNumber() const {return _n;}

	long* getPrimeFactors() const;

	const GField& getField() const {return _gField;}
private:
	long _n;
	GField _gField;
};


#endif //CPP_EX1_GFNUMBER_H
