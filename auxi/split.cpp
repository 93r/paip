#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(const string& s, const string& d, vector<string>& v)
{
	auto skip = s.find(d);
	if (skip == string::npos) {
		v.emplace_back(s.begin(), s.end());
		return;
	}

	auto b = s.begin();
	auto e = b + skip;
	for (
			;
			skip != string::npos
			;
			b = e + d.size(),
			skip = s.find(d, skip + d.size()),
			e = s.begin() + skip
	    )
		v.emplace_back(b, e);

	if (b != s.end())
		v.emplace_back(b, s.end());
}

int main()
{
	string s1 {"hello<COMMA>world<COMMA>mako"};
	string s2 {"hello<COMMA>world<COMMA>"};
	string s3 {"hello<COMMA>world<COMMA"};
	string s4 {"hwfm"};
	string s5 {""};
	string d {"<COMMA>"};
	vector<string> v;

	split(s1, d, v);
	v.push_back("----");
	split(s2, d, v);
	v.push_back("----");
	split(s3, d, v);
	v.push_back("----");
	split(s4, d, v);
	v.push_back("----");
	split(s5, d, v);
	for (auto& i : v)
		std::cout << i << '\n';
}

