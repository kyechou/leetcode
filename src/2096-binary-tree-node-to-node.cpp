/**
 * 2096. Step-By-Step Directions From a Binary Tree Node to Another
 * https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/
 */

#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>

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

class Node {
public:
    TreeNode *frontier;
    string path;

    Node(TreeNode *f, const string &p) : frontier(f), path(p) {}
    void append(char c) { path.push_back(c); }
};

/**
 * n: size of the tree
 * Time: O(n)
 * Space: O(nlog(n))
 */
class Solution1 {
public:
    string getDirections(TreeNode *root, int startValue, int destValue) {
        int foundPaths = 0;
        string startValuePath, destValuePath;
        queue<Node> q;
        q.emplace(Node(root, ""));

        while (!q.empty()) {
            Node node = q.front();
            q.pop();

            // Visit the node
            if (node.frontier->val == startValue) {
                startValuePath = node.path;
                ++foundPaths;
            } else if (node.frontier->val == destValue) {
                destValuePath = node.path;
                ++foundPaths;
            }
            if (foundPaths >= 2) {
                break;
            }

            // Enqueue the children
            if (node.frontier->left) {
                Node nextNode(node);
                nextNode.frontier = node.frontier->left;
                nextNode.append('L');
                q.emplace(std::move(nextNode));
            }
            if (node.frontier->right) {
                Node nextNode(node);
                nextNode.frontier = node.frontier->right;
                nextNode.append('R');
                q.emplace(std::move(nextNode));
            }
        }

        assert(foundPaths == 2);
        size_t i;
        for (i = 0; i < startValuePath.size() && i < destValuePath.size() &&
                    startValuePath[i] == destValuePath[i];
             ++i)
            ;
        string res(startValuePath.size() - i, 'U');
        res += destValuePath.substr(i);
        return res;
    }
};

/**
 * n: size of the tree
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
private:
    string tracePath(TreeNode *root,
                     TreeNode *target,
                     const unordered_map<TreeNode *, TreeNode *> &parentCache) {
        string path;
        TreeNode *node = target;
        while (node != root) {
            auto parent = parentCache.at(node);
            if (parent->left == node) {
                path.push_back('L');
            } else if (parent->right == node) {
                path.push_back('R');
            } else {
                throw runtime_error("");
            }
            node = parent;
        }
        return string(path.rbegin(), path.rend());
    }

public:
    string getDirections(TreeNode *root, int startValue, int destValue) {
        unordered_map<TreeNode *, TreeNode *> parentCache;
        TreeNode *startNode(nullptr), *destNode(nullptr);
        queue<TreeNode *> q;
        q.push(root);
        parentCache.emplace(root, nullptr);

        while (!q.empty()) {
            TreeNode *currNode = q.front();
            q.pop();

            // Visit the node
            if (currNode->val == startValue) {
                startNode = currNode;
            } else if (currNode->val == destValue) {
                destNode = currNode;
            }
            if (startNode != nullptr && destNode != nullptr) {
                break;
            }

            // Enqueue the children
            if (currNode->left) {
                q.push(currNode->left);
                parentCache.emplace(currNode->left, currNode);
            }
            if (currNode->right) {
                q.push(currNode->right);
                parentCache.emplace(currNode->right, currNode);
            }
        }

        assert(startNode != nullptr && destNode != nullptr);
        string startPath = tracePath(root, startNode, parentCache);
        string destPath = tracePath(root, destNode, parentCache);
        size_t i;
        for (i = 0; i < startPath.size() && i < destPath.size() &&
                    startPath[i] == destPath[i];
             ++i)
            ;
        string res(startPath.size() - i, 'U');
        res += destPath.substr(i);
        return res;
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
