/**
 * 3. Longest Substring Without Repeating Characters
 *
 * Given a string, find the length of the longest substring without repeating
 * characters.
 */

#include <string>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxlen = 0;
        unordered_map<char, size_t> char2idx;
        size_t b = 0, e = 0;

        while (e < s.size()) {
            for (; e < s.size() && char2idx.count(s[e]) == 0; ++e) {
                char2idx[s[e]] = e;
            }
            maxlen = ((int)(e - b) > maxlen) ? (e - b) : maxlen;
            if (e >= s.size()) {
                break;
            }

            // s[e] is repeated
            size_t new_b = char2idx[s[e]] + 1;
            for (size_t i = b; i < new_b; ++i) {
                char2idx.erase(s[i]);
            }
            b = new_b;
        }

        return maxlen;
    }
};

int main() {
    return 0;
}
