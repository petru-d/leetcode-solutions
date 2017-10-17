#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Solution
{
    // Shitty first implementation, barely accepted.
    int maxArea2(vector<int>& height)
    {
        auto curr_lr = std::make_pair(-1, -1);
        auto curr_max = 0;

        for (int i = 0; i < height.size() - 1; ++i)
        {
            if (curr_max != 0 && height[i] < height[curr_lr.first]) continue;

            for (int j = 1 + i; j < height.size(); ++j)
            {
                auto area = (j - i) * std::min(height[i], height[j]);
                if (curr_max < area)
                {
                    curr_lr = { i, j };
                    curr_max = area;
                }
            }
        }

        return curr_max;
    }

    int area(const vector<int>& height, std::pair<int, int> lr)
    {
        return (lr.second - lr.first) * std::min(height[lr.first], height[lr.second]);
    }

    int maxArea(vector<int>& height)
    {
        auto l = 0;
        auto r = int(height.size()) - 1;
        auto max = area(height, { l, r });

        while (l < r)
        {
            if (height[l] < height[r])
            {
                auto ll = l;
                if (ll < r && height[ll] <= height[l]) ++ll;
                l = ll;
            }
            else
            {
                auto rr = r;
                if (rr > l && height[rr] <= height[r]) --rr;
                r = rr;
            }

            max = std::max(max, area(height, { l, r }));
        }

        return max;
    }
}

int main()
{
    vector<int> h;

    h = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    cout << Solution::maxArea(h) << endl;


    h = { 1, 2, 4, 3 };
    cout << Solution::maxArea(h) << endl;


    return 0;
}

