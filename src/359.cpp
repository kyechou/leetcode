/**
 * 359. Logger Rate Limiter
 * https://leetcode.com/problems/logger-rate-limiter/
 */

#include <string>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Logger {
private:
    unordered_map<string, int> tsMap;

public:
    Logger() = default;

    bool shouldPrintMessage(int timestamp, string message) {

        auto it = tsMap.find(message);
        if (it == tsMap.end()) {
            tsMap.emplace(message, timestamp);
            return true;
        }

        int prevTimestamp = it->second;

        if (timestamp < prevTimestamp + 10) {
            return false;
        }

        it->second = timestamp;
        return true;
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
