#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    // If an array has a[i] < a[i + 1] then there exists a bigger permutation of it.
    // Since the number of permutations is finite and completely ordered, there exists a next permutation of it.

    // What happens before the last i where a[i] < a[i + 1] is not relevant :
    // next (A | Ai ... An) = A | next (Ai ... An)

    // Since i is the last with that property, it means that
    // ... a[i] < a[i + 1] >= a[i + 2] >= ... >= a[n]

    // If k is the position of the last element with a[i] < a[k]
    // we have a[k-1] >= a[k] >= a[k+1] and since a[i] < a[k] -> a[k-1] > a[i]
    // since a[k] is the last such a[i] < a[k] it means that a[i] >= a[k+1]
    // So basically we can swap a[i] with a[k] and we will still have a descending sequence.

    // This means that the next permutation is 
    // ... a[k] a[n] a[n-1] ... a[k+1] a[i] a[k-1] ... a[i+1]
    void nextPermutation(vector<int>& nums) 
    {
        int N = int(nums.size());
        for (auto i = N - 2; i >= 0; --i)
        {
            // Find i.
            if (nums[i] < nums[i + 1])
            {
                // Find k.
                auto k = N - 1 - int(distance(nums.rbegin(), find_if(nums.rbegin(), nums.rbegin() + N - i - 1,
                    [&nums, i](int kk)
                    {
                        return kk > nums[i];
                    })));

                swap(nums[i], nums[k]);
                reverse(nums.begin() + i + 1, nums.end());
                return;
            }
        }

        // No i found - reverse the whole thing.
        reverse(nums.begin(), nums.end());
    }
}

int main()
{
    vector<int> data;

    data = { 2, 5, 8, 7, 6, 5 }; // 2 6 5 5 7 8
    Solution::nextPermutation(data);
    print_vector(cout, data);
    cout << "\n";


    data = { 1, 2, 3 }; // 1 3 2
    Solution::nextPermutation(data);
    print_vector(cout, data);
    cout << "\n";

    data = { 1, 3, 2 }; // 2 1 3
    Solution::nextPermutation(data);
    print_vector(cout, data);
    cout << "\n";

    data = { 3, 2, 1 }; // 1 2 3
    Solution::nextPermutation(data);
    print_vector(cout, data);
    cout << "\n";

    data = { 1, 1, 5 }; // 1 5 1
    Solution::nextPermutation(data);
    print_vector(cout, data);
    cout << "\n";

    return 0;
}

