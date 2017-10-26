#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    int find_right(vector<int>& nums, int val, int current_right)
    {
        while (nums[current_right] == val)
        {
            --current_right;

            if (-1 == current_right) return -1;
        }

        return current_right;
    }

    int removeElement(vector<int>& nums, int val)
    {
        if (nums.empty()) return 0;

        int right = find_right(nums, val, int(nums.size() - 1));
        
        int left = 0;

        while (left < right)
        {
            if (val != nums[left])
            {
                ++left;
            }
            else
            {
                std::swap(nums[left], nums[right]);
                right = find_right(nums, val, right);
            }
        }

        return 1 + right;
    }
}

int main()
{
    vector<int> nums;

    nums = { 2 };
    cout << Solution::removeElement(nums, 3) << endl;

    nums = { 3 };
    cout << Solution::removeElement(nums, 3) << endl;

    nums = { 3, 2, 2, 3 };
    cout << Solution::removeElement(nums, 3) << endl;

    return 0;
}

