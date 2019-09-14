#include <iostream>
#include "HashMap.hpp"
#include <vector>
int main2()
{
    using bucket = std::vector<std::pair<int, int> >;
	std::vector<bucket> a(32);
	std::vector<bucket> b(16);
	a = b;
	std::cout << a.capacity();
	HashMap<std::string, int> myMap;

	myMap.insert("aacagj", 1);
	myMap.insert("aacag", 2);
	myMap.insert("aacagjl1220", 2);
	assert(myMap.bucketSize("myMapaacagj") == 2);
	return 0;
}


