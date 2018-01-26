#include <vector>
#include <iostream>
#include <bitset>
#include <array>
#include "../utils/printing.h"

using namespace std;

namespace Solution
{
    using sudoku_possibilities_board = array<array<bitset<9>, 9>, 9>;

    // For each element with a single option, constrain the board with it (do the sudoku "cuts")
    // If any elements become single option during a pass, constrain the board with them as well and so on
    // until there are no more single-option elements or the board becomes invalid.
    // If the board becomes invalid, the function returns false but doesn't change its input argument.
    // Otherwise, the function returns true and the input argument is changed to the constrained version.
    bool constrain_board(sudoku_possibilities_board& possible_configurations)
    {
        sudoku_possibilities_board changed_configurations = possible_configurations;

        vector<pair<int, int>> single_option_points;
        for (int l = 0; l < 9; ++l)
            for (int c = 0; c < 9; ++c)
                if (1 == possible_configurations[l][c].count()) single_option_points.emplace_back(l, c);

        // For each element that has an unique option, do its "cuts".

        while (!single_option_points.empty())
        {
            int l = single_option_points.back().first;
            int c = single_option_points.back().second;

            single_option_points.pop_back();

            // Remove the value from the lines except l.
            for (int i = 0; i < 9; ++i)
            {
                if (i == l) continue;

                auto pre_count = changed_configurations[i][c].count();

                changed_configurations[i][c] &= ~changed_configurations[l][c];
                if (0 == changed_configurations[i][c].count()) 
                    return false;
                if (pre_count > 1 && 1 == changed_configurations[i][c].count()) single_option_points.emplace_back(i, c);
            }

            // Remove the value from the columns except c.
            for (int j = 0; j < 9; ++j)
            {
                if (j == c) continue;

                auto pre_count = changed_configurations[l][j].count();

                changed_configurations[l][j] &= ~changed_configurations[l][c];
                if (0 == changed_configurations[l][j].count()) 
                    return false;
                if (pre_count > 1 && 1 == changed_configurations[l][j].count()) single_option_points.emplace_back(l, j);
            }

            // Remove the value from the corresponding mini-square except the [l][c] location.
            int sq_top_left_line = 3 * (l / 3);
            int sq_top_left_column = 3 * (c / 3);
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (sq_top_left_line + i == l && sq_top_left_column + j == c) continue;

                    auto pre_count = changed_configurations[sq_top_left_line + i][sq_top_left_column + j].count();

                    changed_configurations[sq_top_left_line + i][sq_top_left_column + j] &= ~changed_configurations[l][c];
                    if (0 == changed_configurations[sq_top_left_line + i][sq_top_left_column + j].count()) 
                        return false;
                    if (pre_count > 1 && 1 == changed_configurations[sq_top_left_line + i][sq_top_left_column + j].count()) single_option_points.emplace_back(sq_top_left_line + i, sq_top_left_column + j);
                }
        }

        possible_configurations = changed_configurations;
        return true;
    }

    // Returns true if the board is solved (each configuration has only one option.
    // If the board is not solved, returns false and the second argument will be the position with least options (if there are more, one of them).
    bool is_solved(const sudoku_possibilities_board& possibilities_board, pair<int, int>& best_propagation_location)
    {
        bool solved = true;
        size_t min_bits = 9;
        for (int l = 0; l < 9; ++l)
            for (int c = 0; c < 9; ++c)
            {
                auto current_count = possibilities_board[l][c].count();
                if (1 == current_count) continue;
                if (current_count < min_bits)
                {
                    min_bits = current_count;
                    best_propagation_location = { l, c };
                    solved = false;
                }
            }

        return solved;
    }

    // Translates a board in the bitset format back to a simple char array.
    void translate(const sudoku_possibilities_board& possibilities_board, vector<vector<char>>& board)
    {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                if (1 != possibilities_board[i][j].count())
                {
                    board[i][j] = '?';
                    continue;
                }

                uint8_t v = 0;
                auto c = possibilities_board[i][j].to_ulong();
                while ((1ul << v) != c) ++v;
                board[i][j] = '0' + 1 + v;
            }
    }

    bool backtrack_board(sudoku_possibilities_board& board)
    {
        if (!constrain_board(board)) return false;

        pair<int, int> point;
        if (is_solved(board, point)) 
            return true;

        for (int b = 0; b < 9; ++b)
        {
            if (!board[point.first][point.second][b]) continue;

            auto backup_board = board;

            board[point.first][point.second][b] = false;

            if (backtrack_board(board)) 
                return true;

            board = backup_board;
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board)
    {
        sudoku_possibilities_board possible_configurations{
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
            0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
        };

        // Seed the possible configurations with the board.
        for (int l = 0; l < 9; ++l)
            for (int c = 0; c < 9; ++c)
            {
                if ('.' == board[l][c]) continue;
                int val = board[l][c] - '0' - 1; // Decrease with one to basically have a 0 to 8 sudoku - easier to handle in the bitset.

                // At that position, the possible configurations will only contain the value.
                possible_configurations[l][c] = 1ll << val;
            }

        // The first call should always succeed, otherwise the game is invalid. 
        // If the validity of the game needs to be checked, test the first call's value.
        constrain_board(possible_configurations);

        backtrack_board(possible_configurations);

        translate(possible_configurations, board);
    }
}

int main()
{
    vector<vector<char>> board =
    {
        { '.', '.', '.', '2', '.', '.', '.', '6', '3' },
        { '3', '.', '.', '.', '.', '5', '4', '.', '1' },
        { '.', '.', '1', '.', '.', '3', '9', '8', '.' },
        { '.', '.', '.', '.', '.', '.', '.', '9', '.' },
        { '.', '.', '.', '5', '3', '8', '.', '.', '.' },
        { '.', '3', '.', '.', '.', '.', '.', '.', '.' },
        { '.', '2', '6', '3', '.', '.', '5', '.', '.' },
        { '5', '.', '3', '7', '.', '.', '.', '.', '8' },
        { '4', '7', '.', '.', '.', '1', '.', '.', '.' }
    };
    Solution::solveSudoku(board);
    print_vector_vector(cout, board);

    return 0;
}



//{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
//{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
//{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
//{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
//{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
//{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
//{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
//{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
//{ '.', '.', '.', '.', '8', '.', '.', '7', '9' },

//{ '.', '.', '9', '7', '4', '8', '.', '.', '.' },
//{ '7', '.', '.', '.', '.', '.', '.', '.', '.' },
//{ '.', '2', '.', '1', '.', '9', '.', '.', '.' },
//{ '.', '.', '7', '.', '.', '.', '2', '4', '.' },
//{ '.', '6', '4', '.', '1', '.', '5', '9', '.' },
//{ '.', '9', '8', '.', '.', '.', '3', '.', '.' },
//{ '.', '.', '.', '8', '.', '3', '.', '2', '.' },
//{ '.', '.', '.', '.', '.', '.', '.', '.', '6' },
//{ '.', '.', '.', '2', '7', '5', '9', '.', '.' },
