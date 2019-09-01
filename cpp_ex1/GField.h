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
/*****************************************************************************************
                                     Constructors
******************************************************************************************/

    /**
     * @param p The Field Characteristic
     * @param l The Field Degree
     */
    GField(long p, long l): _p(p), _l(l) {assert (isPrime(p) && l > 0);}

	/**
	 * Assign default degree
	 */
	GField(long p): GField(p, 1){};

	/**
	 * Assign default characteristic and degree
	 */
	GField(): GField(2, 1) {}

	/**
	 * Copy ctor
	 */
	GField(GField const &gField): GField(gField._p, gField._l) {}

	/**
	 * Destructor
	 */
	~GField()= default;

/*****************************************************************************************
                                        Getters
******************************************************************************************/

    /**
     * @return Field Characteristic
     */
	inline long getChar() const { return _p; }

	/**
	 * @return Field Degree
	 */
    inline long getDegree() const { return _l; }

    /**
     * @return Field Order
     */
	long getOrder() const;

    /**
     * @param p
     * @return True iff p is prime
     */
	static bool isPrime(long p);

/*****************************************************************************************
                                          misc.
******************************************************************************************/

	/**
	 * @param num1
	 * @param num2
	 * @return greatest common divisor of num1 and num2
	 */
    GFNumber gcd(const GFNumber& num1, const GFNumber& num2) const;

    /**
     * @param k
     * @return a number in the field
     */
	GFNumber createNumber(long k) const;

/*****************************************************************************************
                                       operators
******************************************************************************************/

    /**
     * @param other
     * @return reference to a copy of other
     */
	GField & operator=(const GField &other) = default;

	/**
	 * @param other
	 * @return true iff the fields are equal
	 */
	bool operator==(const GField &other) const {return getOrder() == other.getOrder();}

	/**
	 * @param other
	 * @return true iff the fields are different
	 */
	bool operator!=(const GField &other) const {return getOrder() != other.getOrder();}

    /**
     * @param out output stream
     * @param gField
     * @return reference to output stream after printing gField
     */
	friend std::ostream& operator<<(std::ostream& out, const GField& gField);

	/**
	 * @param in input stream
	 * @param gField
	 * @return reference to input stream after updating gField
	 */
	friend std::istream& operator>>(std::istream& in, GField& gField);

private:
/*****************************************************************************************
                                     data members
******************************************************************************************/

    long _p; /** The Field Characteristic */
	long _l; /** The Field Degree */
};


#endif //CPP_EX1_GFIELD_H
