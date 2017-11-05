#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
    {
        unordered_map<string, vector<string>> representant_to_set;

        for (const auto& s : strs)
        {
            auto rep = s;
            sort(rep.begin(), rep.end());

            representant_to_set[rep].push_back(s);
        }

        vector<vector<string>> solution;
        for (const auto& kv : representant_to_set)
        {
            solution.emplace_back(kv.second);
        }

        return solution;
    }
}

int main()
{
    vector<string> v;
    vector<vector<string>> sol;

    v = { "eat", "tea", "tan", "ate", "nat", "bat" };
    sol = Solution::groupAnagrams(v);
    print_vector_vector(cout, sol);

    return 0;
}

