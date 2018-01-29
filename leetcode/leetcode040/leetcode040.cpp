#include <vector>
#include "../utils/printing.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace Solution
{
    // Each unique candidate.
    vector<int> raw_candidates;

    // How many times each candidate is allowed to be used.
    vector<int> weights;

    // Keep a global for the raw solution / raw candidates / weights size.
    // It is needed everywhere and this makes the code cleaner (?).
    int N;

    // A raw solution consists of a 
    // - vector telling how many times to use each candidate (including zero times).
    // - until which index to look in the candidates list (the backtracking algorithm uses a fixed legth vector, but the solution can be shorter)
    vector<pair<vector<int>, int>> raw_solutions;

    // Translate the raw solutions in the desired format.
    vector<vector<int>> translate()
    {
        vector<vector<int>> result;

        for (const auto& raw_sol : raw_solutions)
        {
            vector<int> translated_solution;

            for (int n = 0; n <= raw_sol.second; ++n)
            {
                translated_solution.insert(end(translated_solution), raw_sol.first[n], raw_candidates[n]);
            }

            result.emplace_back(translated_solution);
        }

        return result;
    }

    void backtrack(int target, vector<int>& partial_solution, int partial_n, int partial_sum)
    {
        // Test reject.
        if (partial_sum > target) 
            return;

        // Test accept. No further exploration after accept - the sum will only increase if we select more.
        if (partial_sum == target)
        {
            raw_solutions.push_back({ partial_solution, partial_n });
            return;
        }

        // There are no more next elements to consider.
        if (partial_n >= N - 1)
        {
            return;
        }

        for (int i = 0; i <= weights[1 + partial_n]; ++i)
        {
            partial_solution[1 + partial_n] = i;
            backtrack(target, partial_solution, 1 + partial_n, partial_sum + i * raw_candidates[1 + partial_n]);
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) 
    {
        // Map each unique candidate to the number of times it can participate in the solution.
        // This value cannot exceed the number of appearances of the unique candidate in the raw candidates list.
        // Also the value cannot exceed the number of times the unique candidate fits in the target.
        unordered_map<int, int> weighted_candidates;
        for (auto c : candidates)
        {
            weighted_candidates[c] = std::min(target / c, 1 + weighted_candidates[c]);
        }

        // Transform the map back into two vectors (easier for backtracking).
        raw_candidates.assign(weighted_candidates.size(), 0);
        weights.assign(weighted_candidates.size(), 0);
        int i = 0;
        for (auto kv: weighted_candidates)
        {
            raw_candidates[i] = kv.first;
            weights[i] = kv.second;
            ++i;
        }

        N = int(raw_candidates.size());

        vector<int> ps(N, 0);
        backtrack(target, ps, -1, 0);

        return translate();
    }
}

int main()
{
    vector<int> candidates = { 10, 1, 2, 7, 6, 1, 5};
    print_vector_vector(cout, Solution::combinationSum2(candidates, 8));

    return 0;
}

