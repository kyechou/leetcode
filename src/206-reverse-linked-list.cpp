/**
 * 206. Reverse Linked List
 * https://leetcode.com/problems/reverse-linked-list/description/
 *
 * Given the head of a singly linked list, reverse the list, and return the
 * reversed list.
 */

#include <catch2/catch_test_macros.hpp>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * n: length of the linked list pointed to by head
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev_node = nullptr;
        ListNode *current = head;
        ListNode *next_node = current ? current->next : nullptr;

        while (current) {
            current->next = prev_node;
            prev_node = current;
            current = next_node;
            next_node = current ? current->next : nullptr;
        }

        return prev_node;
    }
};

TEST_CASE("Title") {
    // Solution s;

    SECTION("") {
        // vector<int> nums = {2, 7, 11, 15};
        // REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        // REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }
}
