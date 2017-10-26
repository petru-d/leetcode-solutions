#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    int removeDuplicates(vector<int>& nums)
    {
        if (nums.empty()) return 0;
        int N = int(nums.size());

        // Find the position of the first duplicate - everything before is uniques.
        int start_garbage = 1;
        while (start_garbage < N && nums[start_garbage - 1] < nums[start_garbage]) ++start_garbage;
        if (start_garbage == N) return N;

        // Find the position of the first number bigger than the last unique.
        int end_garbage = start_garbage;
        while (end_garbage < N && nums[end_garbage] <= nums[start_garbage - 1]) ++end_garbage;
        if (end_garbage == N) return start_garbage;

        while (start_garbage < N && end_garbage < N)
        {
            swap(nums[start_garbage], nums[end_garbage]);
            ++start_garbage;
            ++end_garbage;
            while (end_garbage < N && nums[end_garbage] <= nums[start_garbage - 1]) ++end_garbage;
            if (end_garbage == N) return start_garbage;
        }

        return 0;
    }
}

int main()
{
    vector<int> nums;

    nums = { -1, 0, 0, 0, 0, 3, 3 };
    cout << Solution::removeDuplicates(nums) << endl;

    nums = { 1, 1, 2, 2 };
    cout << Solution::removeDuplicates(nums) << endl;

    nums = { 1, 2, 2 };
    cout << Solution::removeDuplicates(nums) << endl; 

    nums = { 1, 2, 3 };
    cout << Solution::removeDuplicates(nums) << endl; 

    nums = { };
    cout << Solution::removeDuplicates(nums) << endl;

    nums = { 1, 1, 2 };
    cout << Solution::removeDuplicates(nums) << endl;

    return 0;
}

