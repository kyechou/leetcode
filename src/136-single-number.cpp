/**
 * 136. Single Number
 *
 * Given a non-empty array of integers nums, every element appears twice except
 * for one. Find that single one.
 *
 * You must implement a solution with a linear runtime complexity and use only
 * constant extra space.
 */

#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(1)
 */
class Solution1 {
public:
    int singleNumber(const vector<int> &nums) {
        int res = 0;
        for (int n : nums) {
            res ^= n;
        }
        return res;
    }
};

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(n)
 */
class Solution2 {
public:
    int singleNumber(const vector<int> &nums) {
        unordered_set<int> seen_once;
        for (int n : nums) {
            auto it = seen_once.find(n);
            if (it == seen_once.end()) {
                seen_once.insert(n);
            } else {
                seen_once.erase(it);
            }
        }
        assert(seen_once.size() == 1);
        return *seen_once.begin();
    }
};

TEST_CASE("Single Number") {
    Solution1 s;

    SECTION("") {
        CHECK(s.singleNumber({2, 2, 1}) == 1);
        CHECK(s.singleNumber({4, 1, 2, 1, 2}) == 4);
        CHECK(s.singleNumber({1}) == 1);
    }
}
