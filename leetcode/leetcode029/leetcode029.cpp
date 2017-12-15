#include <climits>
#include <iostream>

using namespace std;

namespace Solution
{
    int divide(int dividend, int divisor) 
    {
        if (0 == divisor) return INT_MAX;
        if (1 == divisor) return dividend;
        if (-1 == divisor && dividend == INT_MIN) return INT_MAX;
        if (-1 == divisor) return -dividend;

        bool change_sign = dividend < 0 != divisor < 0;
        int64_t l_dividend = llabs(dividend);
        int64_t l_divisor = llabs(divisor);

        int result = 0;
        while (l_dividend >= l_divisor)
        {
            int64_t temp = l_divisor;
            int current_fit = 1;
            while (l_dividend >= (temp << 1))
            {
                temp <<= 1;
                current_fit <<= 1;
            }
            result += current_fit;
            l_dividend -= temp;
        }

        return change_sign ? -result : result;
    }
}

int main()
{
    cout << Solution::divide(INT_MIN, 2) << "\n";
    cout << Solution::divide(7, 2) << "\n";
    cout << Solution::divide(-7, 2) << "\n";
    cout << Solution::divide(2147483647, 2) << "\n";
    return 0;
}


/*
a / (2^x1 + 2^x2 + ... + 2^xn) = 1 / ((2^x1 + 2^x2 + ... + 2^xn) / a) = 1 / (2^x1 / a + 2^x2 / a + ... + 2^xn / a) = 
= 1 / (1 / (a / 2^x1) + 1 / (a / 2^x2) + ... + 1 / (a / 2^xn)) =

*/


