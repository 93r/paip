#ifndef GPS_V1_1_H_
#define GPS_V1_1_H_

#include <string>
#include <vector>

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
		gps(const symlist& state, const symlist& goals, const oplist& ops);
		bool operator()();
	private:
		bool achieve(const symbol& goal);
		bool apply_op(const op& op);
		bool appropriate_p(const symbol& goal, const op& op) const;
		bool member_p(const symbol& item, const symlist& seq) const;
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

#endif

