#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std::placeholders; // for std::bind's _1

/**
 * Because it's about symbolic computing some symbol types are needed.
 */
typedef std::string symbol;
typedef std::vector<std::string> symlist;
/**
 * An operation
 */
struct op {
	symbol action;
	symlist preconds;
	symlist add_list;
	symlist del_list;
};
/**
 * The plural version of operation
 */
typedef std::vector<op> oplist;

class gps {
	public:
		/**
		 * General Problem Solver: achieve all goals using ops
		 */
		gps(const symlist& state, const symlist& goals, const oplist& ops)
			: state_(state), goals_(goals), ops_(ops) {
				std::sort(state_.begin(), state_.end());
				for (auto& op : ops_) {
					std::sort(op.del_list.begin(), op.del_list.end());
					std::sort(op.add_list.begin(), op.add_list.end());
				}
			}

		/**
		 * The General Problem Solver starts working when called
		 * like a Functor.
		 */
		bool operator()() {
			auto pred = std::bind(&gps::achieve, this, _1);

			return std::all_of(goals_.begin(), goals_.end(), pred);
		}
	private:
		/**
		 * A goal is achieved if it already holds, or if there is an
		 * appropriate op for it that is applicable.
		 */
		bool achieve(const symbol& goal) {
			//std::cout << "Checking " << goal << " membership\n";
			if (member_p(goal, state_)) return true;
			//std::cout << "Checking " << goal << " apply_op\n";
			const auto& any_of_pred = std::bind(&gps::apply_op, this, _1);
			oplist tmp;
			const auto& copy_if_pred = std::bind(&gps::appropriate_p, this, goal, _1);
			std::copy_if(ops_.begin(), ops_.end(), std::back_inserter(tmp), copy_if_pred);
			for (auto& i : tmp) { std::cout << ">> " << i.action << "\n"; }
			return std::any_of(tmp.begin(), tmp.end(), any_of_pred);
		}
		/**
		 * Print a message and update state_ if op is applicable.
		 */
		bool apply_op(const op& op) {
			const symlist& sl = op.preconds;
			auto pred = std::bind(&gps::achieve, this, _1);

			//std::cout << "op-action " << op.action;
			if (std::all_of(sl.begin(), sl.end(), pred)) {
				std::cout << " executing op-action " << op.action << "\n";

				symlist tmp;
				std::set_difference(
						state_.begin(), state_.end(),
						op.del_list.begin(), op.del_list.end(),
						std::back_inserter(tmp)
						);
				state_ = tmp;
				tmp.clear();
				std::set_union(
						state_.begin(), state_.end(),
						op.add_list.begin(), op.add_list.end(),
						std::back_inserter(tmp)
					      );
				state_ = tmp;
				return true;
			}
			//std::cout << " fail!\n";

			return false;
		}
		/**
		 * An op is appropriate to a goal if it is in its add list
		 */
		bool appropriate_p(const symbol& goal, const op& op) const {
			return member_p(goal, op.add_list);
		}
		/**
		 * Is item a member of the sequence?
		 */
		bool member_p(const symbol& item, const symlist& seq) const {
			return std::find(seq.begin(), seq.end(), item) != seq.end();
		}
	private:
		/**
		 * The current state: a list of conditions.
		 */
		symlist state_;
		/**
		 * The goals that have to be achieved.
		 */
		symlist goals_;
		/**
		 * The operations that are used to achieve the goals.
		 */
		oplist ops_;
};

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

