/**
 * 1207. Unique Number of Occurrences
 *
 * Given an array of integers arr, return true if the number of occurrences of
 * each value in the array is unique or false otherwise.
 */

#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * n: length of the input array
 * Time: O(n)
 * Space: O(n)
 */
class Solution1 {
public:
    bool uniqueOccurrences(const vector<int> &arr) {
        unordered_map<int, size_t> freq;

        for (int n : arr) {
            auto it = freq.find(n);
            if (it == freq.end()) {
                freq[n] = 1;
            } else {
                it->second++;
            }
        }

        unordered_set<size_t> occurrences;
        for (const auto &[num, times] : freq) {
            if (occurrences.count(times) > 0) {
                return false; // not unique
            }
            occurrences.insert(times);
        }

        return true; // unique number of occurrences
    }
};

TEST_CASE("Unique Number of Occurrences") {
    Solution1 s;

    SECTION("") {
        CHECK(s.uniqueOccurrences({1, 2, 2, 1, 1, 3}));
        CHECK_FALSE(s.uniqueOccurrences({1, 2}));
        CHECK(s.uniqueOccurrences({-3, 0, 1, -3, 1, 1, 1, -3, 10, 0}));
    }
}
