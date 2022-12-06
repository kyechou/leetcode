/**
 * 1101. The Earliest Moment When Everyone Become Friends
 * https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/
 */

#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Solution {
public:
    int earliestAcq(vector<vector<int>> &logs, int n) {
        map<int, pair<int, int>> sortedLogs;

        for (const auto &log : logs) {
            int ts = log[0];
            int x = log[1];
            int y = log[2];
            sortedLogs.emplace(ts, make_pair(x, y));
        }

        vector<shared_ptr<unordered_set<int>>> groups(n, nullptr);
        // people -> groups

        for (const auto &[ts, couple] : sortedLogs) {
            int x = couple.first;
            int y = couple.second;

            // merge y's group into x's

            if (groups[x] == nullptr) {
                groups[x] = make_shared<unordered_set<int>>();
                groups[x]->insert(x);
            }

            if (groups[y]) {
                auto yGroup = groups[y];
                for (int yAcq : *yGroup) {
                    groups[yAcq] = groups[x];
                }
                groups[x]->merge(*yGroup);
            } else {
                groups[y] = groups[x];
                groups[x]->insert(y);
            }

            if (groups[x]->size() == size_t(n)) {
                return ts;
            }
        }

        return -1;
    }
};

TEST_CASE("Title") {
    Solution s;

    SECTION("") {
        vector<vector<int>> logs1 = {
            {20190101, 0, 1},
            {20190104, 3, 4},
            {20190107, 2, 3},
            {20190211, 1, 5},
            {20190224, 2, 4},
            {20190301, 0, 3},
            {20190312, 1, 2},
            {20190322, 4, 5}
        };
        vector<vector<int>> logs2 = {
            {0, 2, 0},
            {1, 0, 1},
            {3, 0, 3},
            {4, 1, 2},
            {7, 3, 1}
        };
        REQUIRE(s.earliestAcq(logs1, 6) == 20190301);
        REQUIRE(s.earliestAcq(logs2, 4) == 3);
    }
}
