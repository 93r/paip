#include <iostream>
#include <string>
#include <vector>

#include "gps-v1-1.h"

int main() {
	oplist school_ops {
		{
			"drive-son-to-school",
			{"son-at-home", "car-works"},
			{"son-at-school"},
			{"son-at-home"}
		},
		{
			"shop-installs-battery",
			{"car-needs-battery", "shop-knows-problem", "shop-has-money"},
			{"car-works"},
			{}
		},
		{
			"tell-shop-problem",
			{"in-communication-with-shop"},
			{"shop-knows-problem"},
			{}
		},
		{
			"telephone-shop",
			{"know-phone-number"},
			{"in-communication-with-shop"},
			{}
		},
		{
			"lookup-number",
			{"have-phone-book"},
			{"know-phone-number"},
			{}
		},
		{
			"give-shop-money",
			{"have-money"},
			{"shop-has-money"},
			{"have-money"}
		}
	};

	std::cout << "GPS run\n";
	/*
	for (auto& i : school_ops)
		std::cout
			<< i.action
			<< " " << i.preconds.size()
			<< " " << i.add_list.size()
			<< " " << i.del_list.size()
			<< "\n";
			*/

	gps school_solver_1 {
		{"son-at-home", "car-needs-battery", "have-money", "have-phone-book"}, // state
			{"son-at-school"}, // goal
			school_ops
	};

	gps school_solver_2 {
		{"son-at-home", "car-needs-battery", "have-money"},
			{"son-at-school"},
			school_ops
	};

	gps school_solver_3 {
		{"son-at-home", "car-works"},
			{"son-at-school"},
			school_ops
	};
	
	std::cout << "Running Solver 1:\n";
	if (school_solver_1()) std::cout << "Solved!\n";
	else std::cout << "Failed!\n";
	std::cout << "Running Solver 2:\n";
	if (school_solver_2()) std::cout << "Solved!\n";
	else std::cout << "Failed!\n";
	std::cout << "Running Solver 3:\n";
	if (school_solver_3()) std::cout << "Solved!\n";
	else std::cout << "Failed!\n";
	return 0;
}

