#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    bool start_matches(const string& where, int start_match, const string& what)
    {
        int i_what = 0;
        while (start_match < where.size() && i_what < what.size())
        {
            if (where[start_match] != what[i_what]) return false;
            ++start_match; ++i_what;

            if (what.size() == i_what) return true;
        }

        return false;
    }

    int romanToInt(string s)
    {
        static string mapmap[] = {
             "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
             "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
             "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
             "M", "MM", "MMM" };

        int result = 0;
        auto index = 0;
        while (index < s.size())
        {
            for (int i = 29; i >= 0; --i)
            {
                if (start_matches(s, index, mapmap[i]))
                {
                    auto qr = div(i, 9);
                    result += int(pow(10, qr.quot)) * (1 + qr.rem);
                    index += int(mapmap[i].size());
                    break;
                }
            }
        }

        return result;
    }
}

int main()
{
    cout << Solution::romanToInt("MMCMIV");
    return 0;
}

