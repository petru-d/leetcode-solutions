#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Solution
{
    int longestValidParentheses(string s) 
    {
        int N = int(s.length());

        // At the end of the scan, this will contain indices of unmatched parantheses.
        vector<int> indices_of_interest;
        indices_of_interest.reserve(N);
        
        for (int i = 0; i < N; ++i)
        {
            if ('(' == s[i])
            {
                indices_of_interest.push_back(i);
            }
            else //(')' == i)
            {
                if (indices_of_interest.empty() || s[indices_of_interest.back()] != '(')
                    indices_of_interest.push_back(i);
                else
                {
                    indices_of_interest.pop_back();
                }
            }
        }

        // No unmatched parantheses - the complete input is valid.
        if (indices_of_interest.empty()) return N;

        // Some unmatched parantheses - the longest valid is the biggest difference between two consecutive unmatched.
        int biggest_diff = 0;
        int left = -1;
        for (int i : indices_of_interest)
        {
            int diff = i - left - 1;

            if (biggest_diff < diff) biggest_diff = diff;

            left = i;
        }
        if (biggest_diff < N - 1 - left) biggest_diff = N - 1 - left; // Also consider the distance from the last element to end

        return biggest_diff;
    }
}

int main()
{
    cout << Solution::longestValidParentheses("(()") << endl;
    cout << Solution::longestValidParentheses(")()())") << endl;
    return 0;
}

