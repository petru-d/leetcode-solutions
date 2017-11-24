#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace Solution
{
    enum class CutResult
    {
        TooLeft,
        JustRight,
        TooRight
    };

    CutResult testCut(const vector<int>& nums1, const vector<int>& nums2, int k)
    {
        /*
               nums1[k - 1]        |       nums1[k]
        nums2[(M + N) / 2 - k - 1] | nums2[(M + N) / 2 - k]
        */

        auto N = int(nums1.size());
        auto M = int(nums2.size());

        // top-left does not exist, bottom-right might not exist
        if (0 == k)
        {
            auto bottom_left = nums2[(M + N) / 2 - k - 1];
            auto top_right = nums1[k];
            if (bottom_left <= top_right) return CutResult::JustRight;

            // Can go only right from here - means we're too left.
            return CutResult::TooLeft;
        }

        // top-right does not exist, bottom-left might not exist
        if (N == k)
        {
            auto top_left = nums1[k - 1];
            auto bottom_right = nums2[(M + N) / 2 - k];
            if (top_left <= bottom_right) return CutResult::JustRight;

            // Can go only left from here - means we're too right.
            return CutResult::TooRight;
        }

        auto top_left = nums1[k - 1];
        auto top_right = nums1[k];
        auto bottom_left = nums2[(M + N) / 2 - k - 1];
        auto bottom_right = nums2[(M + N) / 2 - k];

        if (std::max(top_left, bottom_left) <= std::min(top_right, bottom_right)) return CutResult::JustRight;

        if (top_right < bottom_left) return CutResult::TooLeft;

        return CutResult::TooRight;
    }

    double evaluateCut(const vector<int>& nums1, const vector<int>& nums2, int k)
    {
        /*
               nums1[k - 1]        |       nums1[k]
        nums2[(M + N) / 2 - k - 1] | nums2[(M + N) / 2 - k]
        */

        auto N = int(nums1.size());
        auto M = int(nums2.size());

        auto top_left = k - 1 >= 0 ? nums1[k - 1] : numeric_limits<int>::min();
        auto top_right = k < N ? nums1[k] : numeric_limits<int>::max();
        auto bottom_left = (M + N) / 2 - k - 1 >= 0 ? nums2[(M + N) / 2 - k - 1] : numeric_limits<int>::min();
        auto bottom_right = (M + N) / 2 - k < M ? nums2[(M + N) / 2 - k] : numeric_limits<int>::max();

        auto left = max(top_left, bottom_left);
        auto right = min(top_right, bottom_right);
        if ((M + N) % 2 == 1) return right;
        return (left + right) / 2.0;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        auto N = int(nums1.size());
        auto M = int(nums2.size());

        if (N > M)
        {
            swap(nums1, nums2);
            swap(N, M);
        }

        if (0 == N)
        {
            if (M % 2 == 1) return nums2[M / 2];
            return (nums2[M / 2 - 1] + nums2[M / 2]) / 2.0;
        }

        // Slicing nums1 at position k (between 0 and N) means left(nums1) has k elements
        // so left (nums2) has to have the other (M + N) / 2 - k elements (slice there).
        int left_edge = 0;
        int right_edge = N;
        while (true)
        {
            if (1 + left_edge >= right_edge)
            {
                if (CutResult::JustRight == testCut(nums1, nums2, left_edge)) return evaluateCut(nums1, nums2, left_edge);
                return evaluateCut(nums1, nums2, right_edge);
            }
            auto pivot = (left_edge + right_edge) / 2;
            auto cutResult = testCut(nums1, nums2, pivot);

            if (CutResult::JustRight == cutResult) return evaluateCut(nums1, nums2, pivot);

            if (CutResult::TooLeft == cutResult) left_edge = pivot;
            else /*if (CutResult::TooRight == cutResult) */ right_edge = pivot;
        }
    }
}

int main()
{
    vector<int> nums1;
    vector<int> nums2;

    nums1 = { 1 };
    nums2 = { 1 };
    cout << Solution::findMedianSortedArrays(nums1, nums2) << endl;

    nums1 = { 1, 2 };
    nums2 = { 3, 4 };
    cout << Solution::findMedianSortedArrays(nums1, nums2) << endl;

    nums1 = { 1, 3 };
    nums2 = { 2 };
    cout << Solution::findMedianSortedArrays(nums1, nums2) << endl;
}

