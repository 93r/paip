#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "gps-v1-1.h"

using namespace std::placeholders; // for std::bind's _1

/**
 * General Problem Solver: achieve all goals using ops
 */
gps::gps(const symlist& state, const symlist& goals, const oplist& ops)
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
bool gps::operator()() {
	auto pred = std::bind(&gps::achieve, this, _1);

	if (std::all_of(goals_.begin(), goals_.end(), pred))
		return true;

	return false;
}

/**
 * A goal is achieved if it already holds, or if there is an
 * appropriate op for it that is applicable.
 */
bool gps::achieve(const symbol& goal) {
	//std::cout << "Checking " << goal << " membership\n";
	if (member_p(goal, state_)) return true;
	//std::cout << "Checking " << goal << " apply_op\n";
	const auto& any_of_pred = std::bind(&gps::apply_op, this, _1);
	oplist tmp;
	const auto& copy_if_pred = std::bind(&gps::appropriate_p, this, goal, _1);
	std::copy_if(ops_.begin(), ops_.end(), std::back_inserter(tmp), copy_if_pred);
	for (auto& i : tmp) { std::cout << ">> " << i.action << "\n"; }
	if (std::any_of(tmp.begin(), tmp.end(), any_of_pred)) return true;
	return false;
}

/**
 * Print a message and update state_ if op is applicable.
 */
bool gps::apply_op(const op& op) {
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
bool gps::appropriate_p(const symbol& goal, const op& op) const {
	return member_p(goal, op.add_list);
}

/**
 * Is item a member of the sequence?
 */
bool gps::member_p(const symbol& item, const symlist& seq) const {
	return std::find(seq.begin(), seq.end(), item) != seq.end();
}

