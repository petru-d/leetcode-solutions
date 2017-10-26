#include <string>
#include <stack>
#include <iostream>

using namespace std;

namespace Solution
{
    char opposite(char p)
    {
        if (')' == p) return '(';
        if (']' == p) return '[';
        if ('}' == p) return '{';

        return 0;
    }
    bool isValid(string s) 
    {
        std::stack<char> simplified;

        int S = int(s.length()) - 1;
        for (int i = 0; i <= S; ++i)
        {
            char c = s[i];
            if ('(' == c || '[' == c || '{' == c)
                simplified.push(c);
            else
            {
                if (simplified.empty() || simplified.top() != opposite(c)) return false;
                simplified.pop();
            }
        }
        return simplified.empty();
    }
}

int main()
{
    cout << Solution::isValid("()") << endl;
    cout << Solution::isValid("()[]{}") << endl;
    cout << Solution::isValid("(]") << endl;
    cout << Solution::isValid("([)]") << endl;
    cout << Solution::isValid("([])") << endl;
    cout << Solution::isValid("]") << endl;

    return 0;
}

