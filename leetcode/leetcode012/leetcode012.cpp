#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
	string intToRoman(int num) 
	{
		if (1 > num || 3999 < num) return "";

		static vector<vector<string>> mapmap = { 
			{ "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
			{ "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" },
			{ "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" },
			{ "M", "MM", "MMM" }
		};

		vector<int> split(4, 0);
		int i = 0;
		while (0 != num)
		{
			auto qr = div(num, 10);
			split[i++] = qr.rem;
			num = qr.quot;
		}

		string result;
		for (i = int(split.size()) - 1; i >= 0; --i)
		{
			if (0 == split[i]) continue;
			result += mapmap[i][split[i] - 1];
		}

		return result;
	}
}

int main()
{
	cout << Solution::intToRoman(3215);
    return 0;
}

