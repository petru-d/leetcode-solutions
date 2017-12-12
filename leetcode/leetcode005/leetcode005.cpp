#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace Solution
{
    // Implementation of Manacher's algorithm
    // http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
    string longestPalindrome(string s)
    {
        if (s.size() <= 1) return s;

        int N = 2 * int(s.length()) + 1;
        vector<int> L(N, 0);
        L[1] = 1;

        int C = 1; //centerPosition 
        int R = 2; //centerRightPosition
        int maxLPSLength = 0;
        int maxLPSCenterPosition = 0;

        for (int i = 2; i < N; i++)
        {
            //currentLeftPosition = 2 * C - i for currentRightPosition = i
            //If currentRightPosition i is within centerRightPosition R
            if (R > i)
                L[i] = min(L[2 * C - i], R - i);

            //Attempt to expand palindrome centered at currentRightPosition i
            //For odd positions, we compare characters and if match then increment LPS Length.
            //For even positions, we just increment LPS by ONE without any character comparison
            while (((i + L[i]) < N && (i - L[i]) > 0) &&
                (((i + L[i] + 1) % 2 == 0) ||
                (s[(i + L[i] + 1) / 2] == s[(i - L[i] - 1) / 2]))) L[i]++;
            
            //If the palindrome centered at currentRightPosition i 
            //expands beyond centerRightPosition R,
            //adjust centerPosition C based on the expanded palindrome.
            if (i + L[i] > R)
            {
                C = i;
                R = i + L[i];
            }

            // Track the best palindrome.
            if (L[i] > maxLPSLength)
            {
                maxLPSLength = L[i];
                maxLPSCenterPosition = i;
            }
        }

        return s.substr((maxLPSCenterPosition - maxLPSLength) / 2, maxLPSLength);
    }
}

int main()
{
    cout << Solution::longestPalindrome("babcbabcbaccba") << endl;
    return 0;
}

