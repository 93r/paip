#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(0));
	std::cout
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		;
	std::cout
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		;
	std::cout
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		<< std::rand() % 6 << "\n"
		;
}

