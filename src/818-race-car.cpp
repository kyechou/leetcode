/**
 * 818. Race Car
 * https://leetcode.com/problems/race-car/
 */

#include <cmath>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Solution {
private:
    unordered_map<int, int> posMap; // pos -> shortest seq length

public:
    int racecar(int target) {
        assert(target >= 0);

        auto it = posMap.find(target);
        if (it != posMap.end()) {
            return it->second;
        }

        int lb = floor(log2(target + 1));
        int ub = lb + 1;

        // 2^lb - 1 == target
        if ((1 << lb) - 1 == target) {
            posMap.emplace(target, lb);
            return lb;
        }

        int minlen = ub + 1 + racecar((1 << ub) - 1 - target);

        for (int backLen = 0; backLen < lb; backLen++) {
            minlen = min(minlen, lb + 1 + backLen + 1 +
                                     racecar(target - ((1 << lb) - 1) +
                                             ((1 << backLen) - 1)));
        }

        posMap.emplace(target, minlen);
        return minlen;
    }
};

TEST_CASE("Title") {
    Solution s;

    SECTION("") {
        REQUIRE(s.racecar(0) == 0);
        REQUIRE(s.racecar(2) == 4);
        REQUIRE(s.racecar(3) == 2);
        REQUIRE(s.racecar(5) == 7);
        REQUIRE(s.racecar(6) == 5);
        REQUIRE(s.racecar(11) == 10);
        REQUIRE(s.racecar(100) == 19);
        REQUIRE(s.racecar(5617) == 41);
    }
}
