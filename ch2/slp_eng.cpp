#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>

using symbol = std::string;
using symlist = std::vector<symbol>;

/**
 * Choose an element from a list at random.
 */
symbol random_elt(const symlist& choices) {
	static struct t {
		t() { std::srand(std::time(0)); }
	} sr;
	return choices[std::rand() % choices.size()];
}

int main() {
	symlist sl {"hello", "world", "from", "mako", "slp", "eng"};

	std::cout
		<< random_elt(sl) << "\n"
		<< random_elt(sl) << "\n"
		<< random_elt(sl) << "\n"
		;
}

