/**
 * 993. Cousins in Binary Tree
 *
 * https://leetcode.com/problems/cousins-in-binary-tree/description/?envType=problem-list-v2&envId=mmspsi0s
 *
 * Given the root of a binary tree with unique values and the values of two
 * different nodes of the tree x and y, return true if the nodes corresponding
 * to the values x and y in the tree are cousins, or false otherwise.
 *
 * Two nodes of a binary tree are cousins if they have the same depth with
 * different parents.
 *
 * Note that in a binary tree, the root node is at the depth 0, and children of
 * each depth k node are at the depth k + 1.
 *
 * Notes
 * - Each node has a unique value.
 * - x != y
 * - x and y exist in the tree.
 */

#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

/**
 * n: size of the binary tree given by `root`.
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
public:
    bool isCousins(TreeNode *root, int x, int y) {
        if (root->val == x || root->val == y) {
            return false;
        }
        // x and y wouldn't be root.

        int x_parent = 0;
        int x_depth = -1;
        int y_parent = 0;
        int y_depth = -1;
        int current_depth = 0;
        queue<pair<TreeNode *, int /*depth*/>> q;
        q.push({root, 0});

        while (!q.empty() && (x_depth == -1 || y_depth == -1)) {
            auto [node, depth] = q.front();
            q.pop();

            if (depth > current_depth) {
                current_depth = depth;
                if ((x_depth != -1 && y_depth == -1) ||
                    (x_depth == -1 && y_depth != -1)) {
                    return false;
                }
            }

            for (TreeNode *child : {node->left, node->right}) {
                if (child) {
                    if (child->val == x) {
                        x_parent = node->val;
                        x_depth = depth + 1;
                    } else if (child->val == y) {
                        y_parent = node->val;
                        y_depth = depth + 1;
                    }
                    q.push({child, depth + 1});
                }
            }
        }

        return (x_depth == y_depth) && (x_parent != y_parent);
    }
};

TEST_CASE("Cousins in Binary Tree") {
    // Solution s;

    SECTION("") {
        // vector<int> nums = {2, 7, 11, 15};
        // REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        // REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }
}
