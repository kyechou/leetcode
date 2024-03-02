/**
 * 15. 3Sum
 *
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the sum
 * of zero.
 *
 * Note:
 * The solution set must not contain duplicate triplets.
 */

#include <algorithm>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Solution {
    vector<pair<int, int>> twoSum(vector<int> &nums, int target) {
        vector<pair<int, int>> ans;

        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (target - nums[i] < nums[j]) {
                --j;
            } else if (target - nums[i] > nums[j]) {
                ++i;
            } else {
                ans.push_back(make_pair(nums[i], nums[j]));
                for (int num = nums[i]; i < j && nums[i] == num; ++i)
                    ;
            }
        }

        return ans;
    }

public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        int last_num = 0;
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end()); // Time O(n*log(n))

        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i != 0 && nums[i] == last_num) {
                continue;
            }
            last_num = nums[i];
            vector<int> right_nums(nums.begin() + i + 1, nums.end());
            auto two_sums = twoSum(right_nums, -nums[i]);

            for (auto pair : two_sums) {
                ans.push_back(vector<int>({nums[i], pair.first, pair.second}));
            }
        }

        return ans;
    }
};

TEST_CASE("3Sum") {
    Solution s;

    SECTION("") {
        vector<int> nums = {-1, 0, 1, 2, -1, -4};
        REQUIRE(s.threeSum(nums) == vector<vector<int>>({
                                        {-1, -1, 2},
                                        {-1, 0,  1}
        }));
    }
    SECTION("") {
        vector<int> nums = {-1, 0, 1, 0};
        REQUIRE(s.threeSum(nums) == vector<vector<int>>({
                                        {-1, 0, 1}
        }));
    }
    SECTION("") {
        vector<int> nums = {-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6};
        REQUIRE(s.threeSum(nums) == vector<vector<int>>({
                                        {-4, -2, 6},
                                        {-4, 0,  4},
                                        {-4, 1,  3},
                                        {-4, 2,  2},
                                        {-2, -2, 4},
                                        {-2, 0,  2}
        }));
    }
    SECTION("") {
        vector<int> nums = {0, 0, 0};
        REQUIRE(s.threeSum(nums) == vector<vector<int>>({
                                        {0, 0, 0}
        }));
    }
}
