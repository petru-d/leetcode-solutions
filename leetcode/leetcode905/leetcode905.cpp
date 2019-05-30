#include "../utils/printing.h"
#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    vector<int> sortArrayByParity(vector<int>& A)
    {
        size_t N = A.size();
        if (0 == N)
            return {};

        size_t afterLastEven = 0;
        size_t firstOdd = N;

        while (afterLastEven < N && A[afterLastEven] % 2 == 0)
            ++afterLastEven;

        while (firstOdd - 1 < N && A[firstOdd - 1] % 2 == 1)
            --firstOdd;

        while (afterLastEven < firstOdd)
        {
            if (A[afterLastEven] % 2 == 0)
                ++afterLastEven;
            else
            {
                std::swap(A[afterLastEven], A[firstOdd - 1]);
                --firstOdd;
            }
        }

        return std::move(A);
    }
}

int main()
{
    vector<int> A = {3, 1, 2, 4};

    print_vector(cout, Solution::sortArrayByParity(A));

    return 0;
}
