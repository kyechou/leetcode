/**
 * 2340. Minimum Adjacent Swaps to Make a Valid Array
 *
 * https://leetcode.com/problems/minimum-adjacent-swaps-to-make-a-valid-array/?envType=problem-list-v2&envId=mmspsi0s
 *
 * You are given a 0-indexed integer array nums.
 *
 * Swaps of adjacent elements are able to be performed on nums.
 *
 * A valid array meets the following conditions:
 *
 *   - The largest element (any of the largest elements if there are multiple)
 *     is at the rightmost position in the array.
 *   - The smallest element (any of the smallest elements if there are multiple)
 *     is at the leftmost position in the array.
 *
 * Return the minimum swaps required to make nums a valid array.
 */

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(1)
 */
class Solution {
public:
    int minimumSwaps(const vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }

        // Find the left-most minimum and the right-most maximum
        int left_most_min_idx = 0;
        int right_most_max_idx = 0;
        int min = nums[0];
        int max = nums[0];
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] < min) {
                min = nums[i];
                left_most_min_idx = i;
            }
            if (nums[i] >= max) {
                max = nums[i];
                right_most_max_idx = i;
            }
        }

        int left_dist = left_most_min_idx - 0;
        int right_dist = nums.size() - 1 - right_most_max_idx;
        return left_dist + right_dist -
               ((right_most_max_idx < left_most_min_idx) ? 1 : 0);
    }
};

TEST_CASE("Minimum Adjacent Swaps to Make a Valid Array") {
    Solution s;

    SECTION("") {
        CHECK(s.minimumSwaps({3, 4, 5, 5, 3, 1}) == 6);
        CHECK(s.minimumSwaps({9}) == 0);
    }
}
