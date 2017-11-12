#include <vector>
#include <iostream>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    int search_first(const vector<int>& nums, int target, int left, int right)
    {
        if (1 + left >= right)
        {
            return target == nums[left] ? left : target == nums[right] ? right : -1;
        }

        int pivot = (left + right) / 2;

        if (nums[pivot] >= target) return search_first(nums, target, left, pivot);

        return search_first(nums, target, pivot, right);
    }

    int search_last(const vector<int>& nums, int target, int left, int right)
    {
        if (1 + left >= right)
        {
            return target == nums[right] ? right : target == nums[left] ? left : -1;
        }

        int pivot = (left + right) / 2;

        if (nums[pivot] <= target) return search_last(nums, target, pivot, right);

        return search_last(nums, target, left, pivot);
    }

    vector<int> searchRange(vector<int>& nums, int target)
    {
        if (nums.empty()) return { -1, -1 };

        auto low = search_first(nums, target, 0, int(nums.size()) - 1);
        if (-1 == low) return { -1, -1 };

        return { low, search_last(nums, target, 0, int(nums.size()) - 1)};
    }
}

int main()
{
    vector<int> nums;

    nums = { 5, 7, 7, 8, 8, 10 };
    print_vector(cout, Solution::searchRange(nums, 8));

    nums = { 5, 7, 8, 8, 8, 8, 8, 10 };
    print_vector(cout, Solution::searchRange(nums, 8));

    nums = { };
    print_vector(cout, Solution::searchRange(nums, 8));

    return 0;
}

