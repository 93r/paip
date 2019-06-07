#include <string>
#include <vector>

using namespace std;

void split(const string& s, const string& d, vector<string>& v)
{
	auto pos = s.find(d);
	if (pos == string::npos) {
		v.emplace_back(s.begin(), s.end());
		return;
	}

	auto b = s.begin();
	for (
			;
			pos != string::npos
			;
			b = s.begin() + pos + d.size(),
			pos = s.find(d, pos + d.size())
	    )
		v.emplace_back(b, s.begin() + pos);

	if (b != s.end())
		v.emplace_back(b, s.end());
}

