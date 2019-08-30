#include <iostream>
#include <cassert>
#include "GFNumber.h"
#include "GField.h"


int main()
{
	GFNumber a, b;

    std::cin >> a >> b;
    std::cin.fail();
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << b - a << std::endl;
    std::cout << b * a << std::endl;

	return 0;
}

