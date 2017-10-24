#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
    struct sum
    {
        int s;
        int i;
        int j;
    };

    int search_adjusted_target(const std::vector<sum>& sums, int adjusted_target, int from, int to)
    {
        if (from + 1 >= to) return abs(adjusted_target - sums[to].s) < abs(adjusted_target - sums[from].s) ? to : from;

        int pivot = (from + to) / 2;
        int pivot_val = sums[pivot].s;

        // Found the actual value - return the position.
        if (adjusted_target == pivot_val)
        {
            return pivot;
        }

        if (adjusted_target < pivot_val)
        {
            return search_adjusted_target(sums, adjusted_target, from, pivot);
        }

        return search_adjusted_target(sums, adjusted_target, pivot, to);
    }

    // Returns an index such that |sums[index] - adjusted_target| is minimal. 
    int search_adjusted_target(const std::vector<sum>& sums, int adjusted_target)
    {
        return search_adjusted_target(sums, adjusted_target, 0, int(sums.size()) - 1);
    }

    // Make a vector of adjusted targets (for each element, keep the difference between the target and it).
    // Make a vector of sums of pairs nums[i] + nums[j], such that i < j and sort it.
    // For each adjusted target, (binary) search for it in the vector of pairs. 
    //  If the adjusted target contributed to the found pair, search around it for the closest that didn't came from the adjusted target.
    // Complexity O(n^2 * log(n)) - accepted but on the slow side.
    int threeSumClosest2(vector<int>& nums, int target)
    {
        auto N = nums.size();

        // nums[i] + nums[j] + nums[k] ~= target means
        // nums[i] + nums[j] ~= target - nums[k]

        // Build the adjusted targets array;
        vector<int> adjusted_targets(N, 0);
        for (int k = 0; k < N; ++k)
        {
            adjusted_targets[k] = target - nums[k];
        }

        // Build and sort the sum combinations.
        auto S = N* (N - 1) / 2;
        vector<sum> sums(S, { 0, 0, 0 });
        int c = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 1 + i; j < N; ++j)
            {
                sums[c] = { nums[i] + nums[j], i, j };
                ++c;
            }
        sort(sums.begin(), sums.end(), [](const sum& l, const sum& r)
        {
            return l.s < r.s;
        });

        // Search each adjusted target in the sum combinations array.
        int global_best_diff = std::numeric_limits<int>::max();
        int global_best_sum = std::numeric_limits<int>::max();
        for (int k = 0; k < N; ++k)
        {
            auto pos = search_adjusted_target(sums, adjusted_targets[k]);

            // sums[pos] might contain k as one of the indices that has produced it.
            // In this case, look for the element of sums with the closest value that wasn't produced by k.
            // Such an element must always exist, as long as we have at least 3 elements in the initial array.
            int l_pos = pos;
            int r_pos = pos;
            int adjusted_pos = pos;
            while (true)
            {
                bool consider_l = (0 <= l_pos && sums[l_pos].i != k && sums[l_pos].j != k);
                bool consider_r = (S - 1 >= r_pos && sums[r_pos].i != k && sums[r_pos].j != k);

                if (!consider_l && !consider_r)
                {
                    --l_pos;
                    ++r_pos;
                    continue;
                }

                auto l_diff = consider_l ? abs(sums[pos].s - sums[l_pos].s) : std::numeric_limits<int>::max();
                auto r_diff = consider_r ? abs(sums[pos].s - sums[r_pos].s) : std::numeric_limits<int>::max();

                adjusted_pos = (r_diff < l_diff) ? r_pos : l_pos;
                break;
            }

            int local_best_diff = abs(target - nums[sums[adjusted_pos].i] - nums[sums[adjusted_pos].j] - nums[k]);

            //Can't get any closer than zero - stop search here.
            if (0 == local_best_diff) return target;

            if (global_best_diff > local_best_diff)
            {
                global_best_diff = local_best_diff;
                global_best_sum = nums[sums[adjusted_pos].i] + nums[sums[adjusted_pos].j] + nums[k];
            }
        }

        return global_best_sum;
    }

    // Sort the input array. 
    // For each element at position i, look for i < j < k that minimize |target - nums[i] - nums[j] - nums[k]|.
    //  Since the array is sorted, we can do this by clamping (alternativelly adjusting the j and k towards eachother).
    int threeSumClosest(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());

        // Keep the best SUM (closest to the target).
        int global_best = std::numeric_limits<int>::max();

        int N = int(nums.size());
        for (int i = 0; i < N - 2; ++i)
        {
            int left = 1 + i;
            int right = N - 1;

            int local_best = std::numeric_limits<int>::max();
            while (left < right)
            {
                // Test if the new sum improves upon our current local best. 
                int sum = nums[i] + nums[left] + nums[right];

                if (target < sum) --right;
                if (target > sum) ++left;

                // Best case - target achieved :D
                if (target == sum) return target;

                // Differences to target might overflow - use more bits.
                if (abs(int64_t(target) - sum) < abs(int64_t(target) - local_best)) local_best = sum;
            }

            // Differences to target might overflow - use more bits.
            if (abs(int64_t(target) - local_best) < abs(int64_t(target) - global_best)) global_best = local_best;
        }

        return global_best;
    }
}

int main()
{

    vector<int> nums;

    nums = { 1, 2, 5, 10, 11 };
    cout << Solution::threeSumClosest(nums, 12) << endl; 

    nums = { -55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33 };
    cout << Solution::threeSumClosest(nums, 0) << endl;

    nums = { -3, -2, -5, 3, -4 };
    cout << Solution::threeSumClosest(nums, -1) << endl;

    nums = { 0, 2, 1, -3 };
    cout << Solution::threeSumClosest(nums, 1) << endl;

    nums = { -1, 2, 1, -4 };
    cout << Solution::threeSumClosest(nums, 1) << endl;

    nums = { 0, 1, 2 };
    cout << Solution::threeSumClosest(nums, 0) << endl;

    cout << endl;

    nums = { 1, 2, 5, 10, 11 };
    cout << Solution::threeSumClosest2(nums, 12) << endl;

    nums = { -55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33 };
    cout << Solution::threeSumClosest2(nums, 0) << endl;

    nums = { -3, -2, -5, 3, -4 };
    cout << Solution::threeSumClosest2(nums, -1) << endl;

    nums = { 0, 2, 1, -3 };
    cout << Solution::threeSumClosest2(nums, 1) << endl;

    nums = { -1, 2, 1, -4 };
    cout << Solution::threeSumClosest2(nums, 1) << endl;

    nums = { 0, 1, 2 };
    cout << Solution::threeSumClosest2(nums, 0) << endl;

    return 0;
}

