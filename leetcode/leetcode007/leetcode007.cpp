#include <iostream>
#include <numeric>

using namespace std;

namespace Solution
{
    int reverse(int x)
    {
        auto negative(x < 0);

        if (negative) 
            x = -x;

        int result = 0;
        while (0 != x)
        {
            auto r = std::div(x, 10);

            //Test for overflow (also handles min int).
            if (result > (2147483647 - r.rem) / 10) return 0;

            result = 10 * result + r.rem;
            x = r.quot;
        }

        return negative ? -result : result;
    }
}

int main()
{
    cout << Solution::reverse(numeric_limits<int>::min());
    return 0;
}

