/**
 * 98. Validate Binary Search Tree
 * https://leetcode.com/problems/validate-binary-search-tree/description/
 *
 * Given the root of a binary tree, determine if it is a valid binary search
 * tree (BST).
 */

#include <climits>
#include <optional>

#include <catch2/catch_test_macros.hpp>

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
 * n: number of nodes in the tree.
 * Time: O(n)
 * Space: O(1) or O(lg n) (including the recursion stack space)
 */
class Solution1 {
public:
    bool
    isValidBSTAndBounded(TreeNode *root, optional<int> min, optional<int> max) {
        if (!root) {
            return true;
        }

        return (!min.has_value() || *min < root->val) &&
               (!max.has_value() || root->val < *max) &&
               isValidBSTAndBounded(root->left, min, root->val) &&
               isValidBSTAndBounded(root->right, root->val, max);
    }

    bool isValidBST(TreeNode *root) {
        return isValidBSTAndBounded(root, {}, {});
    }
};

/**
 * n: number of nodes in the tree.
 * Time: O(n)
 * Space: O(1) or O(lg n) (including the recursion stack space)
 */
class Solution2 { // In-order traversal (recursive)
public:
    bool inorder_strict_increasing(TreeNode *root, optional<int> &value) {
        if (!root) {
            return true;
        }

        if (!inorder_strict_increasing(root->left, value)) {
            return false;
        }
        if (value.has_value() && !(root->val > value)) {
            return false;
        }
        value = root->val;
        return inorder_strict_increasing(root->right, value);
    }

    bool isValidBST(TreeNode *root) {
        optional<int> value;
        return inorder_strict_increasing(root, value);
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
