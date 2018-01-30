#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    int firstMissingPositive(vector<int>& nums) 
    {
        auto N = int(nums.size());

        for (int i = 0; i < N; ++i)
        {
            auto v = nums[i];
            while (1 <= v && v <= N && nums[v - 1] != v)
            {
                swap(nums[i], nums[v - 1]);
                v = nums[i];
            }
        }

        for (int i = 0; i < N; ++i)
        {
            if (nums[i] != i + 1) return i + 1;
        }

        return N + 1;
    }
}

int main()
{
    vector<int> data = { 1, 2, 0 };
    cout << Solution::firstMissingPositive(data);

    data = { 3, 4, -1, 1 };
    cout << Solution::firstMissingPositive(data);

    return 0;
}

