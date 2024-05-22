/**
 * 36. Valid Sudoku
 *
 * https://leetcode.com/problems/valid-sudoku/description/
 *
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules:
 *  - Each row must contain the digits 1-9 without repetition.
 *  - Each column must contain the digits 1-9 without repetition.
 *  - Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9
 *    without repetition.
 *
 * Note:
 *  - A Sudoku board (partially filled) could be valid but is not necessarily
 *    solvable.
 *  - Only the filled cells need to be validated according to the mentioned
 *    rules.
 */

#include <catch2/catch_test_macros.hpp>
#include <cctype>
#include <vector>

using namespace std;

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Solution {
public:
    bool isValid(const vector<vector<char>> &board,
                 size_t row_b,
                 size_t row_e,
                 size_t col_b,
                 size_t col_e) {
        vector<bool> seen(10, false);
        for (size_t i = row_b; i < row_e; ++i) {
            for (size_t j = col_b; j < col_e; ++j) {
                if (isdigit(board[i][j])) {
                    if (seen[board[i][j] - '0']) {
                        return false;
                    }
                    seen[board[i][j] - '0'] = true;
                }
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>> &board) {
        // Check each row
        for (size_t i = 0; i < 9; ++i) {
            if (!isValid(board, i, i + 1, 0, 9)) {
                return false;
            }
        }

        // Check each column
        for (size_t j = 0; j < 9; ++j) {
            if (!isValid(board, 0, 9, j, j + 1)) {
                return false;
            }
        }

        // Check each 3x3 block
        for (size_t block_i = 0; block_i < 9; block_i += 3) {
            for (size_t block_j = 0; block_j < 9; block_j += 3) {
                if (!isValid(board, block_i, block_i + 3, block_j,
                             block_j + 3)) {
                    return false;
                }
            }
        }

        return true;
    }
};

TEST_CASE("Valid Sudoku") {
    // Solution s;

    SECTION("") {
        // vector<int> nums = {2, 7, 11, 15};
        // REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        // REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }
}
