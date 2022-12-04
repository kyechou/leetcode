/**
 * 1293. Shortest Path in a Grid with Obstacles Elimination
 * https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
 */

#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Node {
public:
    size_t x, y;
    int k;

    Node(size_t _x, size_t _y, int _k) : x(_x), y(_y), k(_k) {}
};

/**
 * n: size of the grid
 * Time: O(n x k)
 * Space: O(n x k)
 */
class Solution {
private:
    vector<vector<unordered_map<int, int>>> cost; // [i, j] -> (k -> steps)
    queue<Node> q;

    bool explored(const Node &node, int newSteps) const {
        const auto &stepMap = cost[node.x][node.y];

        for (const auto &[requiredK, steps] : stepMap) {
            if (requiredK <= node.k && steps <= newSteps) {
                return true;
            }
        }

        return false;
    }

public:
    int shortestPath(vector<vector<int>> &grid, int k) {
        cost.resize(grid.size());
        for (size_t i = 0; i < grid.size(); ++i) {
            cost[i].resize(grid[i].size());
            for (size_t j = 0; j < grid[i].size(); ++j) {
                cost[i][j].clear();
            }
        }

        cost.back().back().emplace(0, 0);
        q.emplace(Node(grid.size() - 1, grid.back().size() - 1, 0));

        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            int steps = cost[node.x][node.y][node.k];

            // Up
            if (node.x > 0) {
                Node newNode(node.x - 1, node.y,
                             node.k + grid[node.x - 1][node.y]);
                int newSteps = steps + 1;
                if (newNode.k <= k && !explored(newNode, newSteps)) {
                    cost[newNode.x][newNode.y][newNode.k] = newSteps;
                    q.emplace(move(newNode));
                }
            }
            // Down
            if (node.x < grid.size() - 1) {
                Node newNode(node.x + 1, node.y,
                             node.k + grid[node.x + 1][node.y]);
                int newSteps = steps + 1;
                if (newNode.k <= k && !explored(newNode, newSteps)) {
                    cost[newNode.x][newNode.y][newNode.k] = newSteps;
                    q.emplace(move(newNode));
                }
            }
            // Left
            if (node.y > 0) {
                Node newNode(node.x, node.y - 1,
                             node.k + grid[node.x][node.y - 1]);
                int newSteps = steps + 1;
                if (newNode.k <= k && !explored(newNode, newSteps)) {
                    cost[newNode.x][newNode.y][newNode.k] = newSteps;
                    q.emplace(move(newNode));
                }
            }
            // Right
            if (node.y < grid[node.x].size() - 1) {
                Node newNode(node.x, node.y + 1,
                             node.k + grid[node.x][node.y + 1]);
                int newSteps = steps + 1;
                if (newNode.k <= k && !explored(newNode, newSteps)) {
                    cost[newNode.x][newNode.y][newNode.k] = newSteps;
                    q.emplace(move(newNode));
                }
            }
        }

        // for (auto &row : cost) {
        //     for (auto &cell : row) {
        //         cout << "{";
        //         for (auto &[k, steps] : cell) {
        //             cout << k << ':' << steps << ",";
        //         }
        //         cout << "}, ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        int minSteps = -1;
        for (auto &[k, steps] : cost[0][0]) {
            if (minSteps == -1 || steps < minSteps) {
                minSteps = steps;
            }
        }
        return minSteps;
    }
};

TEST_CASE("Title") {
    Solution s;

    SECTION("") {
        vector<vector<int>> grid = {
            {0, 0},
            {1, 0},
            {1, 0},
            {1, 0},
            {1, 0},
            {1, 0},
            {0, 0},
            {0, 1},
            {0, 1},
            {0, 1},
            {0, 0},
            {1, 0},
            {1, 0},
            {0, 0}
        };
        REQUIRE(s.shortestPath(grid, 4) == 14);
    }
}
