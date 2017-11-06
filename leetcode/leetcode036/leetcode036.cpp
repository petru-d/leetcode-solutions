#include <vector>
#include <iostream>

using namespace std;

namespace Solution
{
    // Can be done in only one traversal by remembering a different mask for each line, column, box.
    bool isValidSudoku(vector<vector<char>>& board)
    {
        constexpr int squareSize = 3;
        constexpr int numSquares = 3;
        constexpr int boardSize = squareSize * numSquares;

        if (boardSize != board.size()) return false;

        auto assimilate_char = [](uint32_t& mask, char c)
        {
            uint32_t bit_j = 1 << (c - '0');
            if (mask & bit_j) return false;
            mask |= bit_j;

            return true;
        };

        uint32_t line_masks[boardSize] = { 0 };
        uint32_t column_masks[boardSize] = { 0 };
        uint32_t box_masks[numSquares][numSquares] = { 0 };

        for (int i = 0; i < boardSize; ++i)
            for (int j = 0; j < boardSize; ++j)
            {
                auto c = board[i][j];
                if ('.' == c) continue;

                auto ass_l = assimilate_char(line_masks[i], c);
                auto ass_c = assimilate_char(column_masks[j], c);
                auto ass_b = assimilate_char(box_masks[i / numSquares][j / numSquares], c);

                if (!ass_l || !ass_c || !ass_b) return false;
            }

        return true;
    }
}

int main()
{
    vector<vector<char>> sudoku;

    sudoku = { 
        {'.', '.', '4', '.', '.', '.', '6', '3', '.'}, 
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
        {'5', '.', '.', '.', '.', '.', '.', '9', '.'}, 
        {'.', '.', '.', '5', '6', '.', '.', '.', '.'}, 
        {'4', '.', '3', '.', '.', '.', '.', '.', '1'}, 
        {'.', '.', '.', '7', '.', '.', '.', '.', '.'}, 
        {'.', '.', '.', '5', '.', '.', '.', '.', '.'}, 
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'} };

    cout << Solution::isValidSudoku(sudoku);

    return 0;
}

