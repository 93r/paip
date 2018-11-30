#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct op {
	std::string action;
	std::vector<std::string> preconds;
	std::vector<std::string> add_list;
	std::vector<std::string> del_list;

	friend std::ostream& operator<<(std::ostream& os, const op& op);
};

std::ostream& operator<<(std::ostream& os, const op& op)
{
	std::cout << "<op>\n";
	std::cout << "<action>" << op.action << "</action>\n";
	std::cout << "<preconds>\n";
	for (auto& i : op.preconds) std::cout << "\t<cond>" << i << "</cond>\n";
	std::cout << "</preconds>\n\n";

	std::cout << "<add_list>\n";
	for (auto& i : op.add_list) std::cout << "\t<add>" << i << "</add>\n";
	std::cout << "</add_list>\n\n";
	
	std::cout << "<del_list>\n";
	for (auto& i : op.del_list) std::cout << "\t<del>" << i << "</del>\n";
	std::cout << "</del_list>\n";
	std::cout << "</op>";
	return os;
}

int main()
{
	std::ifstream in {"school_ops.dat"};

	std::string line;
	std::vector<op> ops;
	while (!in.eof()) {
		in >> line;
		if (in.fail()) break;
		op op_as_xml;
		op_as_xml.action = line;

		{ // preconditions
		std::size_t n = 0;
		in >> n;
		std::string s;
		while (n-- > 0) {
			in >> s;
			op_as_xml.preconds.push_back(s);
		}
		}

		{ // add-list
		std::size_t n = 0;
		in >> n;
		std::string s;
		while (n-- > 0) {
			in >> s;
			op_as_xml.add_list.push_back(s);
		}
		}

		{ // del-list
		std::size_t n = 0;
		in >> n;
		std::string s;
		while (n-- > 0) {
			in >> s;
			op_as_xml.del_list.push_back(s);
		}
		}

		ops.push_back(op_as_xml);
	}

	for (auto& i : ops) std::cout << i << "\n\n";
}

