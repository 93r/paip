#include <iostream>

class cp {
	int i_;
	public:
	cp(int i) : i_(i) { std::cout << "ctor(" << i_ << ")" << std::endl; }
	cp(const cp& other) : i_(other.i_+1) { std::cout << "copy_ctor(" << i_ << ")" << std::endl; }
	int get_i() {return i_;}
};

int main()
{
	cp c1 {1};
	cp c2 {2};

	for (auto i : {c1, c2});
}

