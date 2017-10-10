#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
    string longestCommonPrefix2(vector<string>& strs) 
    {
        if (strs.empty()) return "";
        if (1 == strs.size()) return strs[0];

        string::size_type min_len = { numeric_limits<string::size_type>::max() };
        for (const auto& s : strs)
        {
            if (min_len < s.length()) min_len = s.length();
        }

        auto strs_c { strs.size() };
        for (int i = 0; i < min_len; ++i)
        {
            auto c = strs[0][i];

            for (int j = 1; j < strs_c; ++j)
            {
                if (c != strs[j][i]) return strs[0].substr(0, i);
            }
        }

        return strs[0].substr(0, min_len);
    }

    string longestCommonPrefix(vector<string>& strs)
    {
        if (strs.empty()) return "";
        if (1 == strs.size()) return strs[0];

        sort(strs.begin(), strs.end());
        
        auto& s1 = strs[0];
        auto& s2 = strs[strs.size() - 1];

        auto s1_c = s1.length();
        auto s2_c = s2.length();

        string::size_type i{ 0 };
        while (i < s1_c && i < s2_c)
        {
            if (s1[i] != s2[i]) return s1.substr(0, i);
            ++i;
        }

        return s1_c < s2_c ? s1 : s2;
    }
}

int main()
{
    vector<string> vs;

    vs = { "ana", "are", "apples" };
    cout << Solution::longestCommonPrefix(vs) << endl;

    vs = { "", "a" };
    cout << Solution::longestCommonPrefix(vs) << endl;

    vs = { "ana", "are" };
    cout << Solution::longestCommonPrefix(vs) << endl;
    
    vs = { "ana", "bre" };
    cout << Solution::longestCommonPrefix(vs) << endl;


    return 0;
}

