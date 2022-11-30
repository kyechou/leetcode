/**
 * 1. Two Sum
 *
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 */

#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/*
 * n: length of the array
 * Time: O(n^2)
 * Space: O(n)
 */
class Solution1 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        for (int i = 0; i < (int)nums.size(); ++i) {
            for (int j = i + 1; j < (int)nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return vector<int>({i, j});
                }
            }
        }

        return vector<int>();
    }
};

/*
 * n: length of the array
 * Time: O(n)
 * Space: O(n)
 */
class Solution2 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_multimap<int, int> num2idx; // hash table

        for (int i = 0; i < (int)nums.size(); ++i) {
            num2idx.emplace(nums[i], i);
        }

        for (int i = 0; i < (int)nums.size(); ++i) {
            auto range = num2idx.equal_range(target - nums[i]);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second != i) {
                    return vector<int>({i, it->second});
                }
            }
        }

        return vector<int>();
    }
};

TEST_CASE("Two Sum") {
    Solution1 s1;
    Solution2 s2;

    SECTION("") {
        vector<int> nums = {2, 7, 11, 15};
        REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }

    SECTION("") {
        vector<int> nums = {2, 8, 9, 11, 20, 43, 55, 59};
        REQUIRE(s1.twoSum(nums, 51) == vector<int>({1, 5}));
        REQUIRE(s2.twoSum(nums, 51) == vector<int>({1, 5}));
    }

    SECTION("") {
        vector<int> nums = {3, 2, 4};
        REQUIRE(s1.twoSum(nums, 6) == vector<int>({1, 2}));
        REQUIRE(s2.twoSum(nums, 6) == vector<int>({1, 2}));
    }

    SECTION("") {
        vector<int> nums = {3, 3};
        REQUIRE(s1.twoSum(nums, 6) == vector<int>({0, 1}));
        REQUIRE(s2.twoSum(nums, 6) == vector<int>({0, 1}));
    }
}
