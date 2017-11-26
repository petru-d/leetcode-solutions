#include <vector>
#include <set>
#include "../utils/printing.h"
#include <iostream>

using namespace std;

namespace Solution
{
    void generate_permutations(const vector<int>& nums, vector<int>& partial_solution, int last_good, set<int>& free_numbers, vector<vector<int>>& all_solutions)
    {
        int N = int(nums.size());
        if (last_good == N - 1)
        {
            vector<int> solution(N, 0);
            for (int i = 0; i < N; ++i) solution[i] = nums[partial_solution[i] - 1];
            all_solutions.emplace_back(solution);
            return;
        }
        for (int f : free_numbers)
        {
            auto less_numbers = free_numbers;
            less_numbers.erase(f);
            partial_solution[1 + last_good] = f;
            generate_permutations(nums, partial_solution, last_good + 1, less_numbers, all_solutions);
        }
    }

    vector<vector<int>> permute(vector<int>& nums)
    {
        int N = int(nums.size());

        vector<int> partial_solution(N, 0);
        set<int> all_free; for (int i = 1; i <= N; ++i) all_free.insert(i);
        vector<vector<int>> solutions;
        generate_permutations(nums, partial_solution, -1, all_free, solutions);

        return solutions;
    }
}

int main()
{
    vector<int> v;

    v = { 6, 3, 1 };
    print_vector_vector(cout, Solution::permute(v));

    return 0;
}

