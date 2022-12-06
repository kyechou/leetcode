/**
 * 366. Find Leaves of Binary Tree
 * https://leetcode.com/problems/find-leaves-of-binary-tree/
 */

#include <queue>
#include <unordered_map>
#include <vector>

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
 * n: size of the tree
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
private:
    bool isLeaf(const TreeNode *node) const {
        return node->left == nullptr && node->right == nullptr;
    }

public:
    vector<vector<int>> findLeaves(TreeNode *root) {
        vector<vector<int>> result;
        unordered_map<TreeNode *, TreeNode *> parentMap;
        unordered_map<TreeNode *, int> childrenCounts;
        vector<TreeNode *> currentLeaves, nextLeaves;

        // Initial traversal (BFS)
        queue<TreeNode *> q;
        q.push(root);
        parentMap.emplace(root, nullptr);

        while (!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            int children = 0;
            if (node->left) {
                parentMap[node->left] = node;
                q.push(node->left);
                children++;
            }
            if (node->right) {
                parentMap[node->right] = node;
                q.push(node->right);
                children++;
            }
            childrenCounts[node] = children;
            if (children == 0) {
                currentLeaves.push_back(node);
            }
        }

        while (!currentLeaves.empty()) {
            vector<int> leafValues;
            for (auto &leaf : currentLeaves) {
                leafValues.push_back(leaf->val);
                auto parent = parentMap[leaf];

                if (parent) {
                    childrenCounts[parent]--;
                    if (childrenCounts[parent] == 0) {
                        nextLeaves.push_back(parent);
                    }
                }
            }
            result.emplace_back(move(leafValues));
            currentLeaves = move(nextLeaves);
            nextLeaves.clear();
        }

        return result;
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
