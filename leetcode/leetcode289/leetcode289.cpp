#include "../utils/printing.h"
#include <iostream>
#include <vector>

using namespace std;

namespace Solution
{
    size_t M;
    size_t N;

    size_t get(vector<vector<int>>& board, size_t i, size_t j)
    {
        if (i >= M)
            return 0;
        if (j >= N)
            return 0;

        return board[i][j] & 1;
    }

    void gameOfLife(vector<vector<int>>& board)
    {
        M = board.size();
        if (0 == M)
            return;
        N = board[0].size();

        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0; j < N; ++j)
            {
                size_t neibours = get(board, i - 1, j - 1) + get(board, i - 1, j) + get(board, i - 1, j + 1) +
                                  get(board, i, j - 1) + get(board, i, j + 1) + get(board, i + 1, j - 1) + get(board, i + 1, j) +
                                  get(board, i + 1, j + 1);

                board[i][j] |= neibours << 8;
            }

        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0; j < N; ++j)
            {
                bool live = board[i][j] & 1;
                size_t neibours = board[i][j] >> 8;

                board[i][j] = ((live && (neibours == 2 || neibours == 3)) || (!live && neibours == 3)) ? 1 : 0;
            }
    }
}

int main()
{
    vector<vector<int>> b;

    b = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};

    Solution::gameOfLife(b);

    print_vector_vector(cout, b);

    return 0;
}
