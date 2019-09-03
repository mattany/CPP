#include <iostream>
#include "GFNumber.h"


/**
 * the main function
 */
int main()
{
    GFNumber a, b;

    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << b - a << std::endl;
    std::cout << b * a << std::endl;
    a.printFactors();
    b.printFactors();
    return 0;
}

