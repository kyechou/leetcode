/**
 * 268. Missing Number
 *
 * Given an array nums containing n distinct numbers in the range [0, n], return
 * the only number in the range that is missing from the array.
 */

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of
 * Time: O(n)
 * Space: O(1)
 */
class Solution {
public:
    int missingNumber(const vector<int> &nums) {
        int total_sum = nums.size() * (nums.size() + 1) / 2;
        int actual_sum = 0;
        for (int n : nums) {
            actual_sum += n;
        }
        return total_sum - actual_sum;
    }
};

TEST_CASE("Missing Number") {
    Solution s;

    SECTION("") {
        CHECK(s.missingNumber({3, 0, 1}) == 2);
        CHECK(s.missingNumber({0, 1}) == 2);
        CHECK(s.missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}) == 8);
    }
}
