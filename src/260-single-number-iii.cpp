/**
 * 260. Single Number III
 *
 * Given an integer array nums, in which exactly two elements appear only once
 * and all the other elements appear exactly twice. Find the two elements that
 * appear only once. You can return the answer in any order.
 *
 * You must write an algorithm that runs in linear runtime complexity and uses
 * only constant extra space.
 */

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
    vector<int> singleNumber(const vector<int> &nums) {
        int xor_value = 0;
        for (int n : nums) {
            xor_value ^= n;
        }

        // Find the differing bit position.
        int bit_pos = -1;
        for (int i = 0; i < 32; ++i) {
            if ((xor_value >> i) & 0b1) {
                bit_pos = i;
                break;
            }
        }
        assert(bit_pos != -1);

        int bit_0_xor_value = 0;
        int bit_1_xor_value = 0;
        for (int n : nums) {
            if ((n >> bit_pos) & 0b1) {
                bit_1_xor_value ^= n;
            } else {
                bit_0_xor_value ^= n;
            }
        }
        return {bit_0_xor_value, bit_1_xor_value};
    }
};

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(n)
 */
class Solution2 {
public:
    vector<int> singleNumber(const vector<int> &nums) {
        unordered_set<int> seen;
        for (int n : nums) {
            auto it = seen.find(n);
            if (it == seen.end()) {
                seen.insert(n);
            } else {
                seen.erase(it);
            }
        }
        return vector(seen.begin(), seen.end());
    }
};

TEST_CASE("Single Number III") {
    Solution1 s;

    SECTION("") {
        CHECK((s.singleNumber({1, 2, 1, 3, 2, 5}) == vector{3, 5} ||
               s.singleNumber({1, 2, 1, 3, 2, 5}) == vector{5, 3}));
        CHECK((s.singleNumber({-1, 0}) == vector{-1, 0} ||
               s.singleNumber({-1, 0}) == vector{0, -1}));
        CHECK((s.singleNumber({0, 1}) == vector{1, 0} ||
               s.singleNumber({0, 1}) == vector{0, 1}));
    }
}
