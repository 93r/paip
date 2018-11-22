#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <memory>

int main() {
	std::vector<int> v1 {5, 6, 4, 3, 2, 6, 7, 9, 3};
	std::vector<int> v2 {5, 6, 4, 3, 2, 6, 7, 9, 3};
	std::vector<int> v3 {5, 6, 4, 3, 2, 6, 7, 9, 3};

	std::sort(v2.begin(), v2.end());
	std::nth_element(v3.begin(), v3.begin() + (v3.size()/2), v3.end());

	for (auto v : {std::addressof(v1), std::addressof(v2), std::addressof(v3)}) {
		std::copy(v->begin(), v->end(),
				std::ostream_iterator<decltype(*( v->begin() ))>(std::cout, "-"));
		std::cout
			<< '\n';
	}
}

