#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    int search_max(const vector<int>& nums, int left, int right)
    {
        if (nums[left] < nums[right]) return right;

        if (left + 1 >= right) return nums[left] < nums[right] ? right : left;

        int pivot = (left + right) / 2;

        if (nums[pivot] > nums[left]) return search_max(nums, pivot, right);

        return search_max(nums, left, pivot);
    }

    int search_target(const vector<int>& nums, int left, int right, int target)
    {
        if (left + 1 >= right) return nums[left] == target ? left : nums[right] == target ? right : -1;

        int pivot = (left + right) / 2;

        if (target == nums[pivot]) return pivot;

        if (target < nums[pivot]) return search_target(nums, left, pivot, target);

        return search_target(nums, pivot, right, target);
    }

    // One search for the position of the max, one search for the target
    int search_(vector<int>& nums, int target) 
    {
        int N = int(nums.size());

        if (0 == N) return -1;

        int pos_max = search_max(nums, 0, N - 1);

        if (target >= nums[0]) return search_target(nums, 0, pos_max, target);

        if (N - 1 == pos_max) return -1;

        return search_target(nums, 1 + pos_max, N - 1, target);
    }

    // One search in total.
    int search(vector<int>& nums, int target)
    {
        int N = int(nums.size());
        if (0 == N) return -1;

        int left = 0;
        int right = N - 1;

        while (left <= right)
        {
            int pivot = (left + right) / 2;

            if (nums[pivot] == target) return pivot;

            // If nums[left] ... nums[pivot] is sorted... 
            if (nums[left] <= nums[pivot])
            {
                // ... and target is between nums[left] and nums[pivot] then search between left and pivot.
                if (nums[left] <= target && target <= nums[pivot])
                    right = pivot - 1;
                // ... otherwise search between pivot and right
                else
                    left = pivot + 1;
            }

            // If nums[pivot] ... nums[right] is sorted... 
            if (nums[pivot] <= nums[right])
            {
                // ... and target is between nums[pivot] and nums[right] then search between pivot and right
                if (nums[pivot] <= target && target <= nums[right])
                    left = pivot + 1;
                // ... otherwise search between left and pivot
                else
                    right = pivot - 1;
            }
        }

        return -1;
    }
}

int main()
{
    vector<int> data;

    data = { 5, 1, 3};
    cout << Solution::search(data, 5) << "\n";

    data = { 1, 3, 5 };
    cout << Solution::search(data, 1) << "\n";

    data = { 3, 5, 1 };
    cout << Solution::search(data, 1) << "\n";

    data = { 1, 3 };
    cout << Solution::search(data, 3) << "\n";

    data = { 4, 5, 6, 7, 0, 1, 2 };
    cout << Solution::search(data, 6) << "\n";


    return 0;
}

