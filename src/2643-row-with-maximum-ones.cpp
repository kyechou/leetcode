/**
 * 2643. Row with Maximum Ones
 *
 * https://leetcode.com/problems/row-with-maximum-ones/description/?envType=problem-list-v2&envId=mmspsi0s
 *
 * Given a m x n binary matrix mat, find the 0-indexed position of the row that
 * contains the maximum count of ones, and the number of ones in that row.
 *
 * In case there are multiple rows that have the maximum count of ones, the row
 * with the smallest row number should be selected.
 *
 * Return an array containing the index of the row, and the number of ones in
 * it.
 *
 * mat[i][j] is either 0 or 1.
 */

#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace std;

/**
 * mat: an `m x n` matrix.
 * m: length of mat
 * n: length of mat[]
 * Time: O(mn)
 * Space: O(1)
 */
class Solution {
public:
    vector<int> rowAndMaximumOnes(const vector<vector<int>> &mat) {
        int max_row = -1;
        int max_num_ones = -1;

        for (size_t i = 0; i < mat.size(); ++i) {
            int num_ones = 0;
            for (int val : mat[i]) {
                num_ones += val;
            }
            if (num_ones > max_num_ones) {
                max_row = i;
                max_num_ones = num_ones;
            }
        }

        return {max_row, max_num_ones};
    }
};

TEST_CASE("Row with Maximum Ones") {
    Solution s;

    SECTION("") {
        CHECK(s.rowAndMaximumOnes({
                  {0, 1},
                  {1, 0},
        }) == vector{0, 1});
        CHECK(s.rowAndMaximumOnes({
                  {0, 0, 0},
                  {0, 1, 1},
        }) == vector{1, 2});
        CHECK(s.rowAndMaximumOnes({
                  {0, 0},
                  {1, 1},
                  {0, 0},
        }) == vector{1, 2});
    }
}
