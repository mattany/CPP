#include <iostream>
#include <vector>
int main2()
{
    using bucket = std::vector<std::pair<int, int> >;
	std::vector<bucket> a(32);
	std::vector<bucket> b(16);
	a = b;
	std::cout << a.capacity();
	return 0;
}


