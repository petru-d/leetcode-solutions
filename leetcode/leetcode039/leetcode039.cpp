#include <vector>
#include <iostream>
#include <algorithm>

#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    bool dead(const vector<int>& current_solution)
    {
        return *current_solution.begin() == -1;
    }



    void backtrack(const vector<int>& candidates, int target, const vector<int>& maximas, vector<int>& current_solution, int current_sum)
    {
        if (dead(current_solution)) return;
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        int C = int(candidates.size());

        vector<int> current_solution(C, -1);
        *current_solution.begin() = 0;

        vector<int> maximas(C, 0);
        std::transform(candidates.begin(), candidates.end(), maximas.begin(), [target](int c) {return target / c; });

        backtrack(candidates, target, maximas, current_solution, 0);

        return { maximas };
    }
}

int main()
{
    vector<int> candidates;

    candidates = { 2, 3, 6, 7 };
    print_vector_vector(cout, Solution::combinationSum(candidates, 7));

    return 0;
}
