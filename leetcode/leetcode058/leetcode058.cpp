#include <string>
#include <iterator>

using namespace std;

namespace Solution
{
	int lengthOfLastWord(string s)
	{
		auto startPos = std::rbegin(s);
		while (*startPos == ' ') ++startPos;

		auto pos = std::find(startPos, std::rend(s), ' ');
		return static_cast<int>(std::distance(startPos, pos));
	}
}

int main()
{
    return 0;
}

