/**
 * 729. My Calendar I
 * https://leetcode.com/problems/my-calendar-i/
 */

#include <set>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Entry {
public:
    int start, end;

    Entry(int s, int e) : start(s), end(e) {}
};

bool operator<(const Entry &a, const Entry &b) {
    return a.end <= b.start;
}

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class MyCalendar {
private:
    set<Entry> entries;

public:
    MyCalendar() {}

    bool book(int start, int end) {
        Entry entry(start, end);
        auto res = entries.insert(entry);

        if (res.second) {
            // Merge with the previous or the next entry if possible
            auto it = res.first;

            if (it != entries.begin()) {
                auto prev = --it;
                if (prev->end == start) {
                    Entry merged(prev->start, end);
                    auto n = entries.erase(entries.erase(prev));
                    entries.insert(n, merged);
                }
            } else if (++it != entries.end()) {
                auto next = it;
                if (next->start == end) {
                    Entry merged(start, next->end);
                    auto n = entries.erase(entries.erase(--it));
                    entries.insert(n, merged);
                }
            }
        }

        return res.second;
    }
};

TEST_CASE("Title") {
    MyCalendar cal;

    SECTION("") {
        REQUIRE(cal.book(10, 20) == true);
        REQUIRE(cal.book(15, 25) == false);
        REQUIRE(cal.book(20, 30) == true);
    }
}
