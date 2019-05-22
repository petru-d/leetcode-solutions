#include <iostream>
#include <iterator>
#include <string>
#include <tuple>

using namespace std;

namespace Solution
{
    std::pair<char, char> addBinary(char a, char b, char r)
    {
        if (a == '0' && b == '0')
            return {'0', r};
        if (a == '1' && b == '1')
            return {'1', r};
        if (r == '0')
            return {'0', '1'};
        return {'1', '0'};
    }

    string addBinary(string a, string b)
    {
        string& l = a.length() > b.length() ? a : b;
        string& s = a.length() <= b.length() ? a : b;

        auto S = s.size();

        char r = '0';
        for (auto it = std::rbegin(l); it != std::rend(l); ++it)
        {
            auto dist = std::distance(std::rbegin(l), it);

            std::tie(r, *it) = addBinary(*it, dist >= static_cast<ptrdiff_t>(S) ? '0' : s[S - dist - 1], r);
        }

        if (r == '1')
        {
            l.insert(l.begin(), '1');
        }

        return l;
    }
}

int main()
{
    cout << Solution::addBinary("11", "1") << std::endl;
    cout << Solution::addBinary("1010", "1011") << std::endl;
    return 0;
}
