#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
	std::vector<char> v1 (10);
	std::vector<char> v2 (10);

	//std::fill(v1.begin(), v1.end(), 65);
	//std::fill(v2.begin(), v2.end(), 97);

	for (auto i : {&v1, &v2}) {
		std::fill(i->begin(), i->end(), 66);
	}

	for (auto i : {&v1, &v2}) {
		std::copy(i->begin(), i->end(),
				std::ostream_iterator<decltype(*( i->begin() ))>(std::cout));
		std::cout << "\n";
	}
}

