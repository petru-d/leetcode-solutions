#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());

        vector<vector<int>> solution;

        // ... i ... j ... l ... r ...

        int N = int(nums.size());
        for (int i = 0; i < N - 3; ++i)
        {
            // skip i duplicates
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < N - 2; ++j)
            {
                // skip j duplicates
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int l = j + 1;
                int r = N - 1;
                while (l < r)
                {
                    int sum = nums[i] + nums[j] + nums[l] + nums[r];
                    if (sum == target)
                    {
                        solution.push_back({ nums[l], nums[i], nums[j], nums[r] });

                        // advance and skip l duplicates
                        do { ++l; } while (nums[l] == nums[l - 1] && l < r);

                        // advance and skip r duplicates
                        do { --r; } while (nums[r] == nums[r + 1] && l < r);
                    }
                    else if (sum < target) ++l;
                    else /*if (sum > target)*/ --r;
                }
            }
        }

        return solution;
    }
}

int main()
{
    vector<int> nums;

    nums = { -1, 0, 1, 2, -1, -4 };
    print_vector_vector(cout, Solution::fourSum(nums, -1));

    nums = { 1, 0, -1, 0, -2, 2 };
    print_vector_vector(cout, Solution::fourSum(nums, 0));

    nums = { -3, -2, -1, 0, 0, 1, 2, 3 };
    print_vector_vector(cout, Solution::fourSum(nums, 0));

    nums = { 0, 0, 0, 0 };
    print_vector_vector(cout, Solution::fourSum(nums, 0));

    return 0;
}

