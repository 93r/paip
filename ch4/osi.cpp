#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

int main() {
	std::vector<int> v(20);

	std::iota(v.begin(), v.end(), 1);
	std::copy(v.begin(), v.end() - 1,
			std::ostream_iterator<int>(std::cout, "-"));
	std::cout
		<< *(v.end() - 1)
		<< '\n';
}

