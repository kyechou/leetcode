/**
 * 2034. Stock Price Fluctuation
 * https://leetcode.com/problems/stock-price-fluctuation/
 */

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: Number of records
 * Time: update: O(log(n)), others: O(1)
 * Space: O(n)
 */
class StockPrice {
private:
    unordered_map<int, int> records; // timestamp -> price
    multiset<int> sortedRecords;     // prices
    int latestTimestamp;
    int latestPrice;

public:
    StockPrice() : latestTimestamp(0), latestPrice(0) {}

    void update(int timestamp, int price) {
        auto it = records.find(timestamp);
        if (it == records.end()) {
            // Make a new record
            records.emplace(timestamp, price);
            sortedRecords.insert(price);
            if (timestamp > latestTimestamp) {
                latestTimestamp = timestamp;
                latestPrice = price;
            }
        } else {
            // Update an existing record
            int prevPrice = it->second;
            it->second = price;
            if (prevPrice != price) {
                sortedRecords.erase(sortedRecords.find(prevPrice));
                sortedRecords.insert(price);
            }
            if (latestTimestamp == timestamp) {
                latestPrice = price;
            }
        }
    }

    int current() { return latestPrice; }
    int maximum() { return *sortedRecords.rbegin(); }
    int minimum() { return *sortedRecords.begin(); }
};

TEST_CASE("Title") {
    StockPrice s;

    SECTION("") {
        s.update(38, 2308);
        s.update(47, 7876);
        s.update(58, 1866);
        s.update(43, 121);
        s.update(40, 5339);
        REQUIRE(s.current() == 1866);
        // vector<int> nums = {2, 7, 11, 15};
        // REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        // REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
    }
}
