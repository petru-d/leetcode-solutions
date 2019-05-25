#include "../utils/printing.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

namespace Solution
{
    // l[0] <= r[0]
    bool touch(const vector<int>& l, const vector<int>& r)
    {
        return r[0] < l[1] + 1;
    }

    // l[0] <= r[0]
    void append(vector<int>& to, const vector<int>& what)
    {
        to[1] = std::max(to[1], what[1]);
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};

        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& l, const vector<int>& r) { return l[0] < r[0]; });

        vector<vector<int>> solution = {intervals[0]};

        for (const auto& i : intervals)
        {
            if (touch(*solution.rbegin(), i))
            {
                append(*solution.rbegin(), i);
            }
            else
                solution.push_back(i);
        }

        return solution;
    }
}

int main()
{

    auto v = vector<vector<int>>{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    bool ok = Solution::merge(v) == vector<vector<int>>{{1, 6}, {8, 10}, {15, 18}};
    assert(ok);
    v = vector<vector<int>>{{1, 4}, {5, 6}};
    ok = Solution::merge(v) == vector<vector<int>>{{1, 4}, {5, 6}};
    assert(ok);

    return 0;
}
