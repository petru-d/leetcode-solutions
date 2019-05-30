#include "../utils/printing.h"
#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    void setZeroes(vector<vector<int>>& matrix)
    {
        size_t M = matrix.size();
        if (0 == M)
            return;
        size_t N = matrix[0].size();

        bool firstColHasZero = false;
        for (size_t i = 0; i < M; ++i)
            if (matrix[i][0] == 0)
            {
                firstColHasZero = true;
                break;
            }

        bool firstLineHasZero = false;
        for (size_t j = 0; j < N; ++j)
            if (matrix[0][j] == 0)
            {
                firstLineHasZero = true;
                break;
            }

        for (size_t i = 1; i < M; ++i)
            for (size_t j = 1; j < N; ++j)
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }

        for (size_t i = 1; i < M; ++i)
            if (matrix[i][0] == 0)
                for (size_t j = 0; j < N; ++j)
                    matrix[i][j] = 0;

        for (size_t j = 1; j < N; ++j)
            if (matrix[0][j] == 0)
                for (size_t i = 0; i < M; ++i)
                    matrix[i][j] = 0;

        if (firstLineHasZero)
            for (size_t j = 0; j < N; ++j)
                matrix[0][j] = 0;

        if (firstColHasZero)
            for (size_t i = 0; i < M; ++i)
                matrix[i][0] = 0;
    }
}

int main()
{
    vector<vector<int>> m;

    m = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
    Solution::setZeroes(m);
    print_vector_vector(cout, m);
    return 0;
}
