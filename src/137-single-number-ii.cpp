/**
 * 137. Single Number II
 *
 * Given an integer array nums where every element appears three times except
 * for one, which appears exactly once. Find the single element and return it.
 *
 * You must implement a solution with a linear runtime complexity and use only
 * constant extra space.
 */

#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
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
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int n : nums) {
                sum += (n >> i) & 0b1;
            }
            res |= ((sum % 3) & 0b1) << i;
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
        unordered_map<int, int> seen;
        for (int n : nums) {
            auto it = seen.find(n);
            if (it == seen.end()) {
                seen.insert({n, 1});
            } else {
                if (it->second == 1) {
                    it->second++;
                } else if (it->second == 2) {
                    seen.erase(it);
                } else {
                    assert(false);
                }
            }
        }
        assert(seen.size() == 1);
        return seen.begin()->first;
    }
};

TEST_CASE("Single Number II") {
    Solution1 s;

    SECTION("") {
        CHECK(s.singleNumber({2, 2, 3, 2}) == 3);
        CHECK(s.singleNumber({0, 1, 0, 1, 0, 1, 99}) == 99);
    }
}
