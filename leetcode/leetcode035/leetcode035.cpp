#include <vector>
#include <iostream>

using namespace std;

int search_insert_indexes(const vector<int>& nums, int i_start, int i_end, int target)
{
    if (i_end <= i_start + 1)
    {
        return (target <= nums[i_start]) ? i_start : i_end;
    }

    int i_pivot = (i_start + i_end) / 2;
    int pivot = nums[i_pivot];

    if (target == pivot) return i_pivot;
    if (target < pivot) return search_insert_indexes(nums, i_start, i_pivot, target);
    return search_insert_indexes(nums, i_pivot, i_end, target);
}

int searchInsert(vector<int>& nums, int target) 
{
    return search_insert_indexes(nums, 0, int(nums.size()), target);
}

int main()
{
    vector<int> v = { 1, 3, 5, 6 };
    cout << searchInsert(v, 2) << endl; 
    cout << searchInsert(v, 5) << endl;
    cout << searchInsert(v, 7) << endl;
    cout << searchInsert(v, 0) << endl;

    return 0;
}

