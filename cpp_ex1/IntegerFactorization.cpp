#include <iostream>
#include <assert.h>
#include "GFNumber.h"

void print(GField field);

void print(GField a)
{
    std::cout << a << std::endl<<"Char: "  << a.getChar() << std::endl << "Degree: " <<
              a.getDegree() << std::endl <<"Order: " << a.getOrder() << std::endl;
}

int main()
{
	GField a,b(43,444);

    std::cout << "a == b: " << (a==b) << std::endl;
    std::cout << "a != b: " << (a!=b) << std::endl;
    std::cin >> a;
    print(a);
    print(b);
    b = a;
    print (a);
    print(b);

    assert(a == b);
	return 0;
}

