/**
 * 2158. Amount of New Area Painted Each Day
 * https://leetcode.com/problems/amount-of-new-area-painted-each-day/
 */

#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Interval {
public:
    int start, end;

    Interval(int s, int e) : start(s), end(e) {}
    int size() const { return end - start; }
};

bool operator<(const Interval &a, const Interval &b) {
    return a.end <= b.start;
}

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Solution {
private:
    set<Interval> canvas;

public:
    vector<int> amountPainted(vector<vector<int>> &paint) {
        vector<int> worklog(paint.size());
        int day = 0;

        for (const auto &p : paint) {
            int paintedSize = 0;
            Interval i(p[0], p[1]);
            auto range = canvas.equal_range(i);
            set<Interval>::iterator insertedIt;

            if (range.first == range.second) {
                // There is no overlap on canvas
                insertedIt = canvas.insert(range.second, i);
                paintedSize = i.size();
            } else {
                // There are overlaps with other intervals
                // Calculate the boundaries
                auto last = range.second;
                int lb = min(i.start, range.first->start);
                int ub = max(i.end, (--last)->end);

                // Remove old intervals and calculate the added size
                int oldSize = 0;
                if (lb < i.start) {
                    oldSize -= i.start - lb;
                }
                if (ub > i.end) {
                    oldSize -= ub - i.end;
                }

                auto it = range.first;
                while (it != range.second) {
                    oldSize += it->size();
                    it = canvas.erase(it);
                }

                paintedSize = i.size() - oldSize;
                i = Interval(lb, ub);
                insertedIt = canvas.insert(range.second, i);
            }

            // Merge i with the previous or the next intervals if possible
            // if (insertedIt != canvas.begin()) {
            //     auto prevIt = insertedIt;
            //     prevIt--;

            //     if (prevIt->end == insertedIt->start) {
            //         Interval merged(prevIt->start, insertedIt->end);
            //         auto hint = canvas.erase(canvas.erase(prevIt));
            //         insertedIt = canvas.insert(hint, merged);
            //     }
            // }

            // if (++insertedIt != canvas.end()) {
            //     auto nextIt = insertedIt;
            //     insertedIt--;

            //     if (insertedIt->end == nextIt->start) {
            //         Interval merged(insertedIt->start, nextIt->end);
            //         auto hint = canvas.erase(canvas.erase(insertedIt));
            //         canvas.insert(hint, merged);
            //     }
            // }

            worklog[day] = paintedSize;
            ++day;
        }

        return worklog;
    }

    void clear() { canvas.clear(); }
};

TEST_CASE("Title") {
    Solution s;

    SECTION("") {
        vector<vector<int>> p1 = {
            {1, 4},
            {4, 7},
            {5, 8}
        };
        REQUIRE(s.amountPainted(p1) == vector<int>{3, 3, 1});
        s.clear();
        vector<vector<int>> p2 = {
            {1, 4},
            {5, 8},
            {4, 7}
        };
        REQUIRE(s.amountPainted(p2) == vector<int>{3, 3, 1});
        s.clear();
        vector<vector<int>> p3 = {
            {1, 5},
            {2, 4}
        };
        REQUIRE(s.amountPainted(p3) == vector<int>{4, 0});
        s.clear();
    }
}
