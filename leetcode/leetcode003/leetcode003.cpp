#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Solution
{
    int lengthOfLongestSubstring(string s)
    {
        auto L = int(s.length());
        if (L < 2) return L;

        // No unicode hehe.
        vector<int> mask(255, -1);

        int max = 1;
        int l = 0;
        int r = 0;
        mask[s[r]] = r;

        while (r < L - 1)
        {
            auto where_did_i_see_the_next_element = mask[s[r + 1]];
            if (-1 == where_did_i_see_the_next_element)
            {
                ++r;
                mask[s[r]] = r;
                if (max < r - l + 1) max = r - l + 1;
            }
            else
                // If we just saw the prev element, simply skip all duplicates and reset.
                // This is optional, the else of this if handles it as well, but (maybe) this is faster?
                // Tests on leetcode are not concludent and I'm too lazy to test it myself.
                if (where_did_i_see_the_next_element == r)
                {
                    while (r < L - 1 && s[r] == s[1 + r]) ++r;
                    for (auto& m : mask) m = -1;
                    l = r;
                    mask[s[r]] = r;
                }
                else
                {
                    for (int i = l; i <= where_did_i_see_the_next_element; ++i) mask[s[i]] = -1;
                    l = where_did_i_see_the_next_element + 1;
                    r = r + 1;
                    mask[s[r]] = r;
                }
        }
        return max;
    }
}

int main()
{
    cout << Solution::lengthOfLongestSubstring("abcabcbb") << "\n";

    return 0;
}
