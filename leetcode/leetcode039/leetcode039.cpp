#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    vector<int> _candidates;
    int _target;
    vector<int> _maximas;

    vector<pair<int, vector<int>>> raw_solutions;

    bool good(int curr_sum)
    {
        return curr_sum == _target;
    }

    bool bad(int curr_sum)
    {
        return curr_sum > _target;
    }

    int possible_nexts(int curr_solution_index)
    {
        if (curr_solution_index >= int(_maximas.size()) - 1)
            return -1;

        return _maximas[curr_solution_index + 1];
    }

    vector<int> translate(const pair<int, vector<int>> raw_solution)
    {
        vector<int> result;
        for (int i = 0; i <= get<int>(raw_solution); ++i)
        {
            for (int w = 0; w < get<vector<int>>(raw_solution)[i]; ++w) result.push_back(_candidates[i]);
        }
        return result;
    }

    void backtrack(int curr_solution_index, vector<int>& curr_solution, int curr_sum)
    {
        if (bad(curr_sum)) return;

        if (good(curr_sum))
        {
            raw_solutions.emplace_back(curr_solution_index, curr_solution);
            return; // no further exploration on this line, we can only increase the sum if we select more
        }

        auto n = possible_nexts(curr_solution_index);
        for (int i = 0; i <= n; ++i)
        {
            curr_solution[1 + curr_solution_index] = i;
            backtrack(1 + curr_solution_index, curr_solution, curr_sum + _candidates[1 + curr_solution_index] * i);
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        int C = int(candidates.size());

        _maximas = vector<int>(C, 0);
        std::transform(candidates.begin(), candidates.end(), _maximas.begin(), [target](int c) {return target / c; });

        _candidates = candidates;
        _target = target;

        auto curr_solution = vector<int>(C, -1);
        backtrack(-1, curr_solution, 0);

        vector<vector<int>> solutions;
        for (const auto& r : raw_solutions)
        {
            solutions.emplace_back(translate(r));
        }
        return solutions;
    }
}

int main()
{
    vector<int> candidates;

    candidates = { 2, 3, 6, 7 };
    print_vector_vector(cout, Solution::combinationSum(candidates, 7));

    return 0;
}
