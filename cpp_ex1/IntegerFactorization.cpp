#include <iostream>
#include <cassert>
#include "GFNumber.h"
#include "GField.h"


int main()
{
	GFNumber a, b;

//    std::cin >> a >> b;
//    std::cin.fail();
//    std::cout << a + b << std::endl << a - b << std::endl;
//    std::cout << b - a << std::endl << b * a << std::endl;
	while (true){a.pollardRho(15); std::cout<<std::endl;}

	return 0;
}

