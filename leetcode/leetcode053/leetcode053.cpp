#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
    // Initial implementation.
    int maxSubArray_(vector<int>& nums)
    {
        if (nums.empty()) return 0;

        int N = int(nums.size());

        int l = 0;
        int r = 0;
        int global_best = nums[0];
        int current_sum = nums[0];
        while (r < N - 1)
        {
            // If the current sum is negative it means we found no positive number until now.
            // Swap to the first number that is bigger than the current
            if (0 > current_sum)
            {
                int next = l;
                while (next < N)
                {
                    if (nums[next] > nums[l])
                    {
                        l = r = next;
                        global_best = current_sum = nums[next];
                        break;
                    }
                    ++next;
                }
                if (N == next)
                {
                    return global_best;
                }
                continue;
            }

            // Attempt to expand the current array. 

            // While the element following is positive, expand without any other consideration.
            if (nums[r + 1] >= 0)
            {
                while (r + 1 < N && nums[r + 1] >= 0)
                {
                    ++r;
                    current_sum += nums[r];
                }
                if (global_best < current_sum) global_best = current_sum;
                continue;
            }
            // Sum all the negative elements following after the current array (name SN).
            // If we reach the array end without having found a positive after the negatives, simply break - no expanding or resetting is possible.
            // If the current_sum + SN < 0, it means that "it's not worth" taking those negatives, so we reset the sequence to the first positive
            // Else, expand by chaing the right to the first positive.

            int SN = 0;
            int neg = r + 1;
            while (neg < N - 1 && nums[neg] < 0)
            {
                SN += nums[neg];
                ++neg;
            }
            if (neg == N)
            {
                return global_best;
            }

            if (current_sum + SN < 0)
            {
                l = r = neg;
                current_sum = nums[neg];
                if (global_best < current_sum) global_best = current_sum;
            }
            else
            {
                r = neg;
                current_sum += nums[neg] + SN;
                if (global_best < current_sum) global_best = current_sum;
            }
        }

        return global_best;
    }

    // Simplified implementation (same thing as above in principle, but much cleaner).
    int maxSubArray(vector<int>& nums) 
    {
        if (nums.empty()) return 0;

        int best_sum = nums[0];
        int N = int(nums.size());

        //Skip all leading negatives and zeros, until we find a proper positive number the best sum is the biggest element.
        int l;
        for (l = 0; l < N; ++l)
        {
            if (nums[l] > 0)
            {
                best_sum = nums[l];
                break;
            }
            best_sum = max(nums[l], best_sum);
        }

        int current_sum = best_sum;

        // If we enter this loop, it means that the current sum is zero or positive.
        for (int i = l + 1; i < N; ++i)
        {
            current_sum += nums[i];

            // If we drop below zero, ignore this number - this means resetting the current sum to zero.
            if (current_sum < 0) current_sum = 0;

            best_sum = max(current_sum, best_sum);
        }

        return best_sum;
    }
}

int main()
{
    vector<int> data;

    data = { 1, 2 }; //3
    cout << Solution::maxSubArray(data) << endl;
    
    data = { -2, -1, -3}; //-1
    cout << Solution::maxSubArray(data) << endl;

    data = { 0, -1, 3, 1, -3, 2, 1, 1 }; //5
    cout << Solution::maxSubArray(data) << endl;

    data = { 8,- 19, 5, -4, 20 }; //21
    cout << Solution::maxSubArray(data) << endl;

    data = { -2, 1}; //1
    cout << Solution::maxSubArray(data) << endl;

    data = {-2, 1, -3, 4, -1, 2, 1, -5, 4 }; //6
    cout << Solution::maxSubArray(data) << endl;

    return 0;
}

