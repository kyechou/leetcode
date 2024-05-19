/**
 * 287. Find the Duplicate Number
 *
 * Given an array of integers nums containing n + 1 integers where each integer
 * is in the range [1, n] inclusive.
 *
 * There is only one repeated number in nums, return this repeated number.
 *
 * You must solve the problem without modifying the array nums and uses only
 * constant extra space.
 */

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of the input array
 * Time: O(n lg n)
 * Space: O(lg n)
 */
class Solution1 {
public:
    int find_dup_recursive(const vector<int> &nums, int b, int e) {
        if (b == e) {
            return b;
        }

        int mid = (b + e) / 2;
        size_t lower_size = mid - b + 1;
        size_t nums_in_lower_bracket = 0;
        for (int n : nums) {
            if (n >= b && n <= mid) {
                nums_in_lower_bracket++;
            }
        }

        if (nums_in_lower_bracket > lower_size) {
            return find_dup_recursive(nums, b, mid);
        } else {
            return find_dup_recursive(nums, mid + 1, e);
        }
    }

    int findDuplicate(const vector<int> &nums) {
        return find_dup_recursive(nums, 1, nums.size() - 1);
    }
};

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(1)
 */
class Solution2 {
public:
    int findDuplicate(const vector<int> &nums) {
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        fast = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};

TEST_CASE("Find the Duplicate Number") {
    Solution1 s1;
    Solution2 s2;

    SECTION("") {
        CHECK(s1.findDuplicate({1, 3, 4, 2, 2}) == 2);
        CHECK(s1.findDuplicate({3, 1, 3, 4, 2}) == 3);
        CHECK(s1.findDuplicate({3, 3, 3, 3, 3}) == 3);
        CHECK(s1.findDuplicate({1, 4, 4, 2, 4}) == 4);
        CHECK(s1.findDuplicate({3, 2, 5, 14, 5, 5, 19, 18, 11, 10,
                                1, 4, 5, 5,  5, 5, 12, 5,  17, 5}) == 5);
        CHECK(s2.findDuplicate({1, 3, 4, 2, 2}) == 2);
        CHECK(s2.findDuplicate({3, 1, 3, 4, 2}) == 3);
        CHECK(s2.findDuplicate({3, 3, 3, 3, 3}) == 3);
        CHECK(s2.findDuplicate({1, 4, 4, 2, 4}) == 4);
        CHECK(s2.findDuplicate({3, 2, 5, 14, 5, 5, 19, 18, 11, 10,
                                1, 4, 5, 5,  5, 5, 12, 5,  17, 5}) == 5);
    }
}
