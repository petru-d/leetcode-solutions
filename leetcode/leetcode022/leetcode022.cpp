#include <vector>
#include <string>
#include <set> 
#include <iostream>

#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    // slow solution - generates a lot of duplicates
    vector<string> generateParenthesis2(int n) 
    {
        if (1 == n) return { "()" };

        auto prev = generateParenthesis2(n - 1);

        set<string> result_as_set;
        for (const auto& p : prev)
        {
            result_as_set.emplace("(" + p + ")");

            for (int i = 0; i <= 2 * n - 2; ++i)
            {
                result_as_set.emplace(p.substr(0, i) + "()" + p.substr(i));
            }
        }

        return std::vector<string>(result_as_set.begin(), result_as_set.end());
    }

    void gogo(vector<string>& accumulate_here, const string& current_result, int left_open, int left_closed)
    {
        if (0 == left_open && 0 == left_closed)
        {
            accumulate_here.push_back(current_result);
            return;
        }

        if (left_open > 0)
        {
            gogo(accumulate_here, current_result + "(", left_open - 1, left_closed + 1);
        }

        if (left_closed > 0)
        {
            gogo(accumulate_here, current_result + ")", left_open, left_closed - 1);
        }
    }

    vector<string> generateParenthesis(int n)
    {
        vector<string> accumulate_here;

        gogo(accumulate_here, "", n, 0);

        return accumulate_here;
    }
}

int main()
{
    print_vector(cout, Solution::generateParenthesis(4));
    return 0;
}

