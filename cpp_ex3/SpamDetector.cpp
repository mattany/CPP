#include <iostream>
#include <vector>
int main()
{
    using bucket = std::vector<std::pair<int, int> >;
	std::vector<bucket> a(16);
    for (bucket b: a)
    {
        for (int i = 0; i <100; i++)
        {
            b.emplace_back(1,2);
            std::cout << a.capacity() << " " << a.size() << std::endl;
        }
    }
	return 0;
}