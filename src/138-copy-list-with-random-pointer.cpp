/**
 * 138. Copy List with Random Pointer
 *
 * https://leetcode.com/problems/copy-list-with-random-pointer/description/
 *
 * A linked list of length n is given such that each node contains an additional
 * random pointer, which could point to any node in the list, or null.
 *
 * Construct a deep copy of the list. The deep copy should consist of exactly n
 * brand new nodes, where each new node has its value set to the value of its
 * corresponding original node. Both the next and random pointer of the new
 * nodes should point to new nodes in the copied list such that the pointers in
 * the original list and copied list represent the same list state. None of the
 * pointers in the new list should point to nodes in the original list.
 *
 * Return the head of the copied linked list.
 *
 * The linked list is represented in the input/output as a list of n nodes. Each
 * node is represented as a pair of [val, random_index] where:
 *  - val: an integer representing Node.val
 *  - random_index: the index of the node (range from 0 to n-1) that the random
 *    pointer points to, or null if it does not point to any node.
 */

#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/**
 * n: length of the input list.
 * Time: O(n)
 * Space: O(n)
 */
class Solution1 {
public:
    Node *copyRandomList(Node *head) {
        unordered_map<Node *, Node *> old_to_new_node_map;
        Node *current = head;
        Node *new_curr = nullptr;
        Node *new_prev = nullptr;
        Node *new_head = nullptr;

        while (current) {
            // Copy the current node.
            new_prev = new_curr;
            new_curr = new Node(current->val);
            old_to_new_node_map[current] = new_curr;

            // Update the head & previous node in the new list.
            if (new_head == nullptr) {
                new_head = new_curr;
            }
            if (new_prev) {
                new_prev->next = new_curr;
            }

            current = current->next;
        }

        // Populate the random pointers.
        current = head;
        new_curr = new_head;
        while (current && new_curr) {
            if (current->random) {
                new_curr->random = old_to_new_node_map.at(current->random);
            }
            current = current->next;
            new_curr = new_curr->next;
        }

        return new_head;
    }
};

/**
 * n: length of the input list.
 * Time: O(n)
 * Space: O(1)
 *
 * old list:  *    *    *    *    *    *    *    *
 *            |   /|   /|   /|   /|   /|   /|   /|   ...
 *            v /  v /  v /  v /  v /  v /  v /  v /
 * new list:  *    *    *    *    *    *    *    *
 */
class Solution2 {
public:
    Node *copyRandomList(Node *head) {
        Node *curr = head;
        Node *new_curr = nullptr;
        Node *new_head = nullptr;

        while (curr) {
            // Copy the current node.
            new_curr = new Node(curr->val);
            new_curr->next = curr->next;
            new_curr->random = curr->random;
            curr->next = new_curr;

            // Update the head and previous node in the new list.
            if (new_head == nullptr) {
                new_head = new_curr;
            }

            curr = new_curr->next;
        }

        // Populate the random pointers.
        new_curr = new_head;
        while (new_curr) {
            new_curr->random =
                new_curr->random ? new_curr->random->next : nullptr;
            new_curr = new_curr->next ? new_curr->next->next : nullptr;
        }

        // Revert back the next pointers.
        curr = head;
        new_curr = new_head;
        while (curr) {
            curr->next = new_curr->next;
            new_curr->next = new_curr->next ? new_curr->next->next : nullptr;
            curr = curr->next;
            new_curr = new_curr->next;
        }

        return new_head;
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
