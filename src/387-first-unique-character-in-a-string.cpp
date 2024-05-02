/**
 * 387. First Unique Character in a String
 * https://leetcode.com/problems/first-unique-character-in-a-string/description/
 *
 * Given a string s, find the first non-repeating character in it and return its
 * index. If it does not exist, return -1.
 *
 * 1 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 */

#include <list>
#include <optional>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

using namespace std;

/**
 * n: length of s
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
public:
    int firstUniqChar(string s) {
        list<int> nrc_to_index;
        unordered_map<char, optional<list<int>::iterator>> chars;

        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];

            if (auto map_it = chars.find(c); map_it != chars.end()) {
                // not unique - remove c from nrc_to_index.
                auto lit = map_it->second;
                if (lit.has_value()) {
                    nrc_to_index.erase(*lit);
                }
                map_it->second.reset();
            } else {
                // is unique - insert c into nrc_to_index.
                nrc_to_index.push_back(i);
                auto lit = nrc_to_index.end();
                lit--;
                chars.insert({c, lit});
            }
        }

        return nrc_to_index.empty() ? -1 : *nrc_to_index.begin();
    }
};

TEST_CASE("First Unique Character in a String") {
    Solution s;

    SECTION("Examples") {
        CHECK(s.firstUniqChar("leetcode") == 0);
        CHECK(s.firstUniqChar("loveleetcode") == 2);
        CHECK(s.firstUniqChar("aabb") == -1);
        CHECK(s.firstUniqChar("aadadaad") == -1);
    }
}
