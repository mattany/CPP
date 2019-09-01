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
/*****************************************************************************************
                                     Constructors
******************************************************************************************/

    /**
     * @param n number
     * @param gField field
     */
    GFNumber(long n, const GField &gField) : _gField(gField)
    {
        _n = modulo(n);
    }

    /**
     * default ctor
     */
    GFNumber() : GFNumber(0, GField())
    {}

    /**
     * @param n number
     * default field ctor
     */
    GFNumber(long n) : GFNumber(n, GField())
    {}

    /**
     * copy ctor
     * @param other
     */
    GFNumber(const GFNumber &other) : GFNumber(other._n, other._gField)
    {}

    /**
     * destructor
     */
    ~GFNumber()
    = default;

/*****************************************************************************************
                                        Getters
******************************************************************************************/

    /**
     * @return the number
     */
    long getNumber() const
    { return _n; }

    /**
     * @return the field
     */
    const GField &getField() const
    { return _gField; }

    /**
     * @param size reference to size of array
     * @return array of factors
     */
    GFNumber *getPrimeFactors(size_t &size) const;

    /**
     * print formatted factors
     */
    void printFactors() const;

    /**
     * @return true iff this._n is prime.
     */
    bool getIsPrime() const
    { return GField::isPrime(_n); }

/*****************************************************************************************
                                       operators
******************************************************************************************/

    /**
     * @param other
     * @return a reference to a copy of other
     */
    GFNumber &operator=(const GFNumber &other)= default;

    /**
     * @param other
     * @return result
     */
    GFNumber operator+(const GFNumber &other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator+=(const GFNumber &other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator-(const GFNumber &other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator-=(const GFNumber &other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator*(const GFNumber &other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator*=(const GFNumber &other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator%(const GFNumber &other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator%=(const GFNumber &other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator+(long other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator+=(long other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator-(long other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator-=(long other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator*(long other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator*=(long other);

    /**
     * @param other
     * @return result
     */
    GFNumber operator%(long other) const;

    /**
     * @param other
     * @return result
     */
    GFNumber &operator%=(long other);

    /**
     * @param other
     * @return true iff this == other
     */
    bool operator==(const GFNumber &other) const;

    /**
     * @param other
     * @return true iff this != other
     */
    bool operator!=(const GFNumber &other) const;

    /**
     * @param other
     * @return true iff this <= other
     */
    bool operator<=(const GFNumber &other) const;

    /**
     * @param other
     * @return true iff this >= other
     */
    bool operator>=(const GFNumber &other) const;

    /**
     * @param other
     * @return true iff this > other
     */
    bool operator>(const GFNumber &other) const;

    /**
     * @param other
     * @return true iff this < other
     */
    bool operator<(const GFNumber &other) const;

    /**
     * @param out output stream
     * @param gfNumber
     * @return reference to output stream after printing gfNumber
     */
    friend std::ostream &operator<<(std::ostream &out, const GFNumber &gfNumber);

    /**
     * @param in input stream
     * @param gfNumber
     * @return reference to input stream after assigning values to gfNumber
     */
    friend std::istream &operator>>(std::istream &in, GFNumber &gfNumber);

private:
/*****************************************************************************************
                                     data members
******************************************************************************************/

    long _n;        /** the number */
    GField _gField; /** the field */

/*****************************************************************************************
                                     private methods
******************************************************************************************/

    /**
     * @param n
     * @return random number between 1 and n-1
     */
    long rng(long n) const;

    /**
     * @param n
     * @return result of x^2 + 1 as GFNumber (to prevent overflow)
     */
    inline GFNumber f(const GFNumber &n) const
    { return GFNumber(n._n * n._n + 1, n._gField); }

    /**
     * appends the value to the array.
     * @param val value to add
     * @param array reference to an array
     * @param size old size of array
     */
    void append(long val, long *&array, size_t &size) const;

    /**
     * @param n
     * @return modulized value according to the field.
     */
    long modulo(long n) const
    { return (n >= 0) ? (n % _gField.getOrder()) : (n % _gField.getOrder() + _gField.getOrder()); }

    /**
     * @param number
     * @param factors array
     * @param size of array
     * @return true iff succeeded in finding factors.
     */
    bool pollardRho(long &number, long *(&factors), size_t &size) const;

    /**
     * put the prime factors comprising n in factors array
     * @param n number
     * @param factors array
     * @param size of array
     */
    void naiveSearch(long n, long *(&factors), size_t &size) const;

    /**
     * divide by 2 and append factors array while even
     * @param number number
     * @param factors array
     * @param size of array
     */
    void halve(long &number, long *&factors, size_t &size) const;
};


#endif //CPP_EX1_GFNUMBER_H
