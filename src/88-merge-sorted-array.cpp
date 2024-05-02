/**
 * 88. Merge Sorted Array
 * https://leetcode.com/problems/merge-sorted-array/description/
 *
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing
 * order, and two integers m and n, representing the number of elements in nums1
 * and nums2 respectively.
 *
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 *
 * The final sorted array should not be returned by the function, but instead be
 * stored inside the array nums1. To accommodate this, nums1 has a length of m +
 * n, where the first m elements denote the elements that should be merged, and
 * the last n elements are set to 0 and should be ignored. nums2 has a length of
 * n.
 */

#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * m: length of nums1
 * n: length of nums2
 * Time: O(m+n)
 * Space: O(m+n)
 */
class Solution {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        vector<int> res;
        res.reserve(m + n);

        int i = 0;
        int j = 0;

        while (i < m && j < n) {
            if (nums2[j] < nums1[i]) {
                res.push_back(nums2[j]);
                ++j;
            } else {
                res.push_back(nums1[i]);
                ++i;
            }
        }

        // Append the remaining elements.
        if (i < m) {
            res.insert(res.end(), nums1.begin() + i, nums1.begin() + m);
        } else if (j < n) {
            res.insert(res.end(), nums2.begin() + j, nums2.begin() + n);
        }

        // Copy res back to nums1.
        nums1 = res;
    }
};

TEST_CASE("Merge Sorted Array") {
    Solution s;

    SECTION("Example 1") {
        vector<int> nums1 = {1, 2, 3, 0, 0, 0};
        vector<int> nums2 = {2, 5, 6};
        s.merge(nums1, 3, nums2, 3);
        REQUIRE(nums1 == vector<int>({1, 2, 2, 3, 5, 6}));
    }

    SECTION("Example 2") {
        vector<int> nums1 = {1};
        vector<int> nums2 = {};
        s.merge(nums1, 1, nums2, 0);
        REQUIRE(nums1 == vector<int>({1}));
    }

    SECTION("Example 3") {
        vector<int> nums1 = {0};
        vector<int> nums2 = {1};
        s.merge(nums1, 0, nums2, 1);
        REQUIRE(nums1 == vector<int>({1}));
    }
}
