/**
 * 715. Range Module
 * https://leetcode.com/problems/range-module/
 */

#include <set>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Range {
public:
    int begin, end;

    Range(int b, int e) : begin(b), end(e) {} // assert(b <= e);

    bool contains(const Range &other) const {
        return this->begin <= other.begin && other.end <= this->end;
    }

    bool empty() const { return begin >= end; }

    void merge(const Range &other) {
        // Assume other overlaps with this
        begin = min(begin, other.begin);
        end = max(end, other.end);
    }
};

class RangeLT {
public:
    bool operator()(const Range &a, const Range &b) const {
        return a.end <= b.begin;
    }
};

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class RangeModule {
private:
    set<Range, RangeLT> ranges;

public:
    RangeModule() = default;

    void addRange(int left, int right) {
        Range newRange(left, right);
        auto [firstRange, lastRange] = ranges.equal_range(newRange);
        auto it = firstRange;

        for (it = firstRange; it != lastRange; it = ranges.erase(it)) {
            newRange.merge(*it);
        }

        // Insert the new range
        // Merge with the previous and/or the next range if possible

        if (it != ranges.begin()) {
            auto prev = --it;
            it++;
            if (prev->end == newRange.begin) {
                newRange.merge(*prev);
                ranges.erase(prev);
            }
        }

        if (it != ranges.end()) {
            if (it->begin == newRange.end) {
                newRange.merge(*it);
                it = ranges.erase(it);
            }
        }

        ranges.insert(it, std::move(newRange));
    }

    bool queryRange(int left, int right) {
        Range targetRange(left, right);
        auto it = ranges.find(targetRange);
        if (it != ranges.end()) {
            return it->contains(targetRange);
        }
        return false;
    }

    void removeRange(int left, int right) {
        vector<Range> rangesToBeInserted;
        Range targetRange(left, right);
        auto [firstRange, lastRange] = ranges.equal_range(targetRange);
        auto it = firstRange;

        for (it = firstRange; it != lastRange; it = ranges.erase(it)) {
            // (*it) - targetRange;
            Range r1(it->begin, targetRange.begin);
            Range r2(targetRange.end, it->end);

            if (!r1.empty()) {
                rangesToBeInserted.emplace_back(std::move(r1));
            }
            if (!r2.empty()) {
                rangesToBeInserted.emplace_back(std::move(r2));
            }
        }

        for (const auto &range : rangesToBeInserted) {
            ranges.insert(it, range);
        }
    }
};

TEST_CASE("Title") {
    SECTION("") {
        RangeModule rm;
        rm.addRange(10, 20);
        rm.removeRange(14, 16);
        REQUIRE(rm.queryRange(10, 14) == true);
        REQUIRE(rm.queryRange(13, 15) == false);
        REQUIRE(rm.queryRange(16, 17) == true);
    }
}
