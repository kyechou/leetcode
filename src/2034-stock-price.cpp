/**
 * 2034. Stock Price Fluctuation
 * https://leetcode.com/problems/stock-price-fluctuation/
 */

#include <queue>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Record {
public:
    int price;
    bool expired;

    Record(int p) : price(p), expired(false) {}
};

class RecordLT {
public:
    bool operator()(Record *const &a, Record *const &b) {
        return a->price < b->price;
    }
};

class RecordGT {
public:
    bool operator()(Record *const &a, Record *const &b) {
        return a->price > b->price;
    }
};

/**
 * n: Number of records
 * Time: average case O(1)
 * Space: O(n)
 */
class StockPrice {
private:
    vector<Record *> expiredRecords;
    unordered_map<int, Record *> records; // timestamp -> price
    priority_queue<Record *, vector<Record *>, RecordLT> maxq;
    priority_queue<Record *, vector<Record *>, RecordGT> minq;
    int latestTimestamp;
    int latestPrice;

public:
    StockPrice() : latestTimestamp(0), latestPrice(0) {}
    ~StockPrice() {
        for (auto rec : expiredRecords) {
            delete rec;
        }
        for (auto [ts, rec] : records) {
            delete rec;
        }
    }

    void update(int timestamp, int price) {
        auto it = records.find(timestamp);
        if (it == records.end()) {
            // Make a new record
            Record *rec = new Record(price);
            records.emplace(timestamp, rec);
            maxq.push(rec);
            minq.push(rec);

            if (timestamp > latestTimestamp) {
                latestTimestamp = timestamp;
                latestPrice = price;
            }
        } else {
            // Update an existing record
            auto oldRec = it->second;
            records.erase(it);
            oldRec->expired = true;
            expiredRecords.push_back(oldRec);

            Record *newRec = new Record(price);
            records.emplace(timestamp, newRec);
            maxq.push(newRec);
            minq.push(newRec);

            if (timestamp == latestTimestamp) {
                latestPrice = price;
            }
        }
    }

    int current() { return latestPrice; }

    int maximum() {
        Record *rec = maxq.top();
        while (rec->expired) {
            maxq.pop();
            rec = maxq.top();
        }
        return rec->price;
    }

    int minimum() {
        Record *rec = minq.top();
        while (rec->expired) {
            minq.pop();
            rec = minq.top();
        }
        return rec->price;
    }
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
    }
}
