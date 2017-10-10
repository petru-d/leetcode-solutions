#include <string>
#include <iostream>

using namespace std;

namespace Solution
{
    int char_hash(char c)
    {
        return int(c);
    }

    int str_hash(const string& to_hash, int from, int to)
    {
        int result = 0;
        for (auto i = from; i < to; ++i)
        {
            result += char_hash(to_hash[i]);
        }

        return result;
    }

    //no checks
    bool str_equal(const string& haystack, int pos, const string& needle)
    {
        return 0 == memcmp(haystack.data() + pos, needle.data(), needle.size());
    }

    int strStr(string haystack, string needle) 
    {
        if (needle.empty()) return 0;

        auto haystack_c = int(haystack.size());
        auto needle_c = int(needle.size());
        if (haystack_c < needle_c) return -1;

        auto needle_hash = str_hash(needle, 0, needle_c);
        auto curr_haystack_hash = str_hash(haystack, 0, needle_c);

        int current_index = 0;
        do
        {
            if (needle_hash == curr_haystack_hash) 
            {
                if (str_equal(haystack, current_index, needle)) return current_index;
            }
            ++current_index;
            if (current_index + needle_c > haystack_c) break;
            curr_haystack_hash = curr_haystack_hash - char_hash(haystack[current_index - 1]) + char_hash(haystack[current_index -1 + needle_c]);
        } while (true);

        return -1;
    }
}

int main()
{
    cout << Solution::strStr("gigel", "ig") << endl;
    cout << Solution::strStr("gigel", "el") << endl;
    return 0;
}

