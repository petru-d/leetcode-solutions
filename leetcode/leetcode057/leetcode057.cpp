#include "../utils/printing.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    size_t bsearch(const vector<vector<int>>& intervals, const vector<int>& i, size_t start, size_t end)
    {
        auto pi = (start + end) / 2;

        const auto& p = intervals[pi];

        if (p[0] == i[0])
            return pi;

        if (start + 1 >= end)
        {
            if (i[0] < intervals[start][0])
                return start;
            return end;
        }

        if (i[0] < p[0])
            return bsearch(intervals, i, start, pi);
        return bsearch(intervals, i, pi, end);
    }

    bool overlap(const vector<int>& a, const vector<int>& b)
    {
        return (b[0] <= a[0] && a[0] <= b[1]) || (b[0] <= a[1] && a[1] <= b[1]) || (a[0] <= b[0] && b[0] <= a[1]) ||
               (a[0] <= b[1] && b[1] <= a[1]);
    }

    void expand(vector<int>& interval, const vector<int>& expansion)
    {
        interval[0] = std::min(interval[0], expansion[0]);
        interval[1] = std::max(interval[1], expansion[1]);
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
    {
        if (intervals.empty())
            return {newInterval};

        auto pos = bsearch(intervals, newInterval, 0, intervals.size());

        // Outside to the right.
        if (pos >= intervals.size())
        {
            if (overlap(newInterval, *intervals.rbegin()))
                expand(*intervals.rbegin(), newInterval);
            else
                intervals.push_back(newInterval);
            return intervals;
        }

        // If the interval touches the one on the left, start from there.
        if (pos > 0 && overlap(newInterval, intervals[pos - 1]))
        {
            --pos;
            expand(intervals[pos], newInterval);
        }
        // If the interval touches the one on its position, unify them and start from there.
        else if (overlap(intervals[pos], newInterval))
        {
            expand(intervals[pos], newInterval);
        }
        else
        {
            intervals.insert(intervals.begin() + pos, newInterval);
            return intervals;
        }

        vector<vector<int>> solution;
        for (size_t i = 0; i <= pos; ++i)
        {
            solution.push_back(intervals[i]);
        }
        size_t i = pos + 1;
        for (; i < intervals.size(); ++i)
        {
            if (overlap(*solution.rbegin(), intervals[i]))
                expand(*solution.rbegin(), intervals[i]);
            else
                break;
        }
        for (size_t j = i; j < intervals.size(); ++j)
        {
            solution.push_back(intervals[j]);
        }
        return solution;
    }
}

int main()
{
    vector<vector<int>> v;
    vector<int> i;

    v = {{1, 3}, {6, 9}};
    i = {2, 5};
    print_vector_vector(cout, Solution::insert(v, i));

    v = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    i = {4, 8};
    print_vector_vector(cout, Solution::insert(v, i));

    v = {{1, 5}};
    i = {2, 3};
    print_vector_vector(cout, Solution::insert(v, i));

    v = {{1, 5}};
    i = {1, 7};
    print_vector_vector(cout, Solution::insert(v, i));

    v = {{1, 5}};
    i = {0, 0};
    print_vector_vector(cout, Solution::insert(v, i));

    return 0;
}
