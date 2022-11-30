/**
 * 2. Add Two Numbers
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 */

#include <catch2/catch_test_macros.hpp>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ~ListNode() { delete next; }
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carry = 0;
        ListNode *sum = l1;

        while (l2 || carry) {
            if (l2) {
                l1->val += l2->val;
                l2 = l2->next;
            }
            l1->val += carry;
            carry = l1->val / 10;
            l1->val %= 10;

            if (!l1->next && (l2 || carry)) {
                l1->next = new ListNode(0);
            }
            l1 = l1->next;
        }

        return sum;
    }
};

TEST_CASE("Add Two Numbers") {
    // Solution s1, s2;

    // SECTION("") {
    //     vector<int> nums = {2, 7, 11, 15};
    //     REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
    //     REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    // }

    // SECTION("") {
    //     vector<int> nums = {2, 8, 9, 11, 20, 43, 55, 59};
    //     REQUIRE(s1.twoSum(nums, 51) == vector<int>({1, 5}));
    //     REQUIRE(s2.twoSum(nums, 51) == vector<int>({1, 5}));
    // }

    // SECTION("") {
    //     vector<int> nums = {3, 2, 4};
    //     REQUIRE(s1.twoSum(nums, 6) == vector<int>({1, 2}));
    //     REQUIRE(s2.twoSum(nums, 6) == vector<int>({1, 2}));
    // }

    // SECTION("") {
    //     vector<int> nums = {3, 3};
    //     REQUIRE(s1.twoSum(nums, 6) == vector<int>({0, 1}));
    //     REQUIRE(s2.twoSum(nums, 6) == vector<int>({0, 1}));
    // }
}
