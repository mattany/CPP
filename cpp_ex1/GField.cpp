//
// Created by mattan on 8/27/19.
//


#include <cassert>
#include "GField.h"
#include "GFNumber.h"
#include <algorithm>

/*****************************************************************************************
                                        Getters
******************************************************************************************/

/**
 * @return The Field Order
 */
long GField::getOrder() const
{
    long ret = 1;
    for (long i = 0; i < _l; i++)
    {
        ret *= _p;
    }
    return ret;
}

/**
 * @param p
 * @return True iff p is prime
 */
bool GField::isPrime(long p)
{
    p = std::labs(p);
    if (p < 2)
    {
        return false;
    }
    long root = floor(sqrt((double) p));
    for (long i = 2; i <= root; i++)
    {
        if (p % i == 0)
        {
            return false;
        }
    }
    return true;
}

/*****************************************************************************************
                                          misc.
******************************************************************************************/

/**
 * @param num1
 * @param num2
 * @return greatest common divisor of num1 and num2
 */
GFNumber GField::gcd(const GFNumber &num1, const GFNumber &num2) const
{
    assert(num1 != 0 || num2 != 0);
    assert(num1.getField() == num2.getField());
    assert(*this == num2.getField());
    long a = num1.getNumber(), b = num2.getNumber();
    return GFNumber(std::__gcd(a, b), num1.getField());

}

/**
 * @param k
 * @return a number in the field
 */
GFNumber GField::createNumber(long k) const
{ return GFNumber(k, *this); }

/*****************************************************************************************
                                       operators
******************************************************************************************/

/**
 * @param out output stream
 * @param gField
 * @return reference to output stream after printing gField
 */
std::ostream &operator<<(std::ostream &out, const GField &gField)
{
    out << "GF(" << gField._p << "**" << gField._l << ")";
    return out;
}

/**
 * @param in input stream
 * @param gField
 * @return reference to input stream after updating gField
 */
std::istream &operator>>(std::istream &in, GField &gField)
{
    long p, l;
    in >> p >> l;
    assert(!in.fail());
    assert(GField::isPrime(p) && l > 0);
    gField._p = p;
    gField._l = l;
    return in;
}


