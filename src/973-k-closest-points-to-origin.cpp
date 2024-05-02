/**
 * 973. K Closest Points to Origin
 * https://leetcode.com/problems/k-closest-points-to-origin/description/
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the
 * X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 *
 * The distance between two points on the X-Y plane is the Euclidean distance
 * (i.e., √((x1 - x2)^2 + (y1 - y2)^2)).
 *
 * You may return the answer in any order. The answer is guaranteed to be unique
 * (except for the order that it is in).
 */

#include <cassert>
#include <queue>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Closer {
public:
    // a < b
    bool operator()(const vector<int> &a, const vector<int> &b) {
        assert(a.size() >= 2 && b.size() >= 2);
        return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
    }
};

/**
 * n: total number of points
 * k: the number of closest points to find
 * Time: O(n lg k)
 * Space: O(k)
 */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        Closer closer;
        priority_queue<vector<int>, vector<vector<int>>, Closer> q;

        for (const auto &point : points) {
            if (q.size() < (size_t)k) {
                q.push(point);
                continue;
            }
            if (closer(point, q.top())) { // point < q.top
                q.pop();
                q.push(point);
            }
        }

        // Dump elements from a max heap to a vector.
        // Alternatively we can inherit the priority queue class and access the
        // private member to get the underlying vector.
        vector<vector<int>> res;
        res.reserve(k);
        while (!q.empty()) {
            res.push_back(q.top());
            q.pop();
        }
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
