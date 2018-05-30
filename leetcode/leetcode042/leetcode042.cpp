#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    //The amount of trapped water is the filled skyline (buildings and water together) minus the skyline itself.
    int trap(vector<int>& height)
    {
        auto N = int(height.size());
        if (0 == N) return 0;

        int filled_skyline = 0;
        int skyline = 0;

        //Compute the skyline and the position of the highest building.
        int max_index = 0;
        for (int i = 0; i < N; ++i)
        {
            skyline += height[i];
            if (height[i] > height[max_index]) max_index = i;
        }

        //Compute the filled skyline until the highest building. It looks like an ascending stair.
        int left = 0;
        for (int i = 0; i < max_index; ++i)
        {
            if (height[i] > left)
            {
                left = height[i];
            }
            filled_skyline += left;
        }

        //Compute the filled skyline until the highest building, starting from right. It looks like a descending stair (ascending if looking from right).
        int right = 0;
        for (int i = N - 1; i > max_index; --i)
        {
            if (height[i] > right)
            {
                right = height[i];
            }
            filled_skyline += right;
        }

        //Add the highest buidling to the filled skyline
        filled_skyline += height[max_index];

        return filled_skyline - skyline;
    }
}

int main()
{
    vector<int> data = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    cout << Solution::trap(data);


    return 0;
}

