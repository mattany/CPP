#include <iostream>
#include <vector>
int main()
{
	std::vector<int> a{1,2,3};
	std::vector<int> b = a;
	b[2]++;
	std::cout<< b[2] << " " << a[2];
	std::cout << "Hello, World!" << std::endl;
	return 0;
}