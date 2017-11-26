#include <string>
#include <iostream>

using namespace std;

namespace Solution
{
    string multiply(string num1, string num2) 
    {
        auto N1 = int(num1.size());
        auto N2 = int(num2.size());
        string result(N1 + N2, '0');

        for (int i = N1 - 1; i >= 0; --i)
        {
            int carry = 0;
            for (int j = N2 - 1; j >= 0; --j)
            {
                auto tmp = std::div((num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry, 10);
                result[i + j + 1] = char(tmp.rem + '0');
                carry = tmp.quot;
            }
            result[i] = char(carry + '0');
        }

        auto pos_not_zero = result.find_first_not_of('0');
        if (string::npos != pos_not_zero)
        {
            return result.substr(pos_not_zero);
        }

        return "0";
    }
}

int main()
{
    cout << Solution::multiply("98", "9") << "\n";

    cout << Solution::multiply("12", "13") << "\n";

    return 0;
}

