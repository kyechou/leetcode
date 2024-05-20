/**
 * 19. Remove Nth Node from End of List
 *
 * Given the head of a linked list, remove the n-th node from the end of the
 * list and return its head.
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
 * n: length of the input list.
 * Time: O(n)
 * Space: O(1)
 */
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *x = head;
        ListNode *y = head;
        ListNode *y_pre = nullptr;

        // Advance x forward `n` steps.
        for (int i = 0; i < n; ++i) {
            if (x == nullptr) {
                return nullptr;
            }
            x = x->next;
        }

        // Advance both x and y forward until x == null
        while (x) {
            x = x->next;
            y_pre = y;
            y = y->next;
        }

        // Remove the node at y.
        if (y_pre) {
            y_pre->next = y->next;
        } else {
            head = y->next;
        }

        return head;
    }
};

TEST_CASE("Remove Nth Node from End of List") {
    // Solution s;

    SECTION("") {
        // vector<int> nums = {2, 7, 11, 15};
        // REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        // REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }
}
