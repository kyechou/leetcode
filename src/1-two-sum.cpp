/**
 * 1. Two Sum
 *
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 */

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of the array
 * Time: O(n^2)
 * Space: O(n)
 */
class Solution1 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        for (int i = 0; i < (int)nums.size(); ++i) {
            for (int j = i + 1; j < (int)nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return vector<int>({i, j});
                }
            }
        }

        return vector<int>();
    }
};

/**
 * n: length of the array
 * Time: O(n)
 * Space: O(n)
 */
class Solution2 {
public:
    bool hasTwoSum(vector<int> &nums, int target) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(target - num) > 0) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }

    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_multimap<int, int> num2idx; // hash table

        for (int i = 0; i < (int)nums.size(); ++i) {
            num2idx.emplace(nums[i], i);
        }

        for (int i = 0; i < (int)nums.size(); ++i) {
            auto range = num2idx.equal_range(target - nums[i]);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second != i) {
                    return vector<int>({i, it->second});
                }
            }
        }

        return vector<int>();
    }
};

class Pair {
private:
    // _a is always <= _b.
    int _a = 0;
    int _b = 0;
    friend class PairEq;
    friend class PairHash;

public:
    Pair(size_t a, size_t b) {
        if (a <= b) {
            _a = a;
            _b = b;
        } else {
            _a = b;
            _b = a;
        }
    }

    vector<int> get_vector() const { return {_a, _b}; }
};

class PairEq {
public:
    bool operator()(const Pair &a, const Pair &b) const {
        return a._a == b._a && a._b == b._b;
    }
};

class PairHash {
public:
    size_t operator()(const Pair &p) const { return p._a ^ p._b; }
};

/**
 * n: length of the array
 * Time: O(n)
 * Space: O(n)
 */
class Solution3 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_set<Pair, PairHash, PairEq> res;

        // Build the num2idx index map.
        unordered_map<int, unordered_set<size_t>>
            num2idx; // num -> set(indices)
        for (size_t i = 0; i < nums.size(); ++i) {
            auto it = num2idx.find(nums[i]);
            if (it == num2idx.end()) {
                num2idx.insert({nums[i], unordered_set<size_t>{i}});
            } else {
                it->second.insert(i);
            }
        }

        for (size_t i = 0; i < nums.size(); ++i) {
            auto it = num2idx.find(target - nums[i]);
            if (it != num2idx.end()) {
                auto indices = it->second;
                indices.erase(i); // Cannot reuse the same element.
                for (size_t other_idx : indices) {
                    res.insert(Pair(i, other_idx));
                }
            }
        }

        if (res.empty()) {
            return vector<int>();
        } else {
            return res.begin()->get_vector();
        }
    }
};

TEST_CASE("Two Sum") {
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    SECTION("") {
        vector<int> nums = {2, 7, 11, 15};
        REQUIRE(s1.twoSum(nums, 9) == vector<int>({0, 1}));
        REQUIRE(s2.twoSum(nums, 9) == vector<int>({0, 1}));
        REQUIRE(s3.twoSum(nums, 9) == vector<int>({0, 1}));
    }

    SECTION("") {
        vector<int> nums = {2, 8, 9, 11, 20, 43, 55, 59};
        REQUIRE(s1.twoSum(nums, 51) == vector<int>({1, 5}));
        REQUIRE(s2.twoSum(nums, 51) == vector<int>({1, 5}));
        REQUIRE(s3.twoSum(nums, 51) == vector<int>({1, 5}));
    }

    SECTION("") {
        vector<int> nums = {3, 2, 4};
        REQUIRE(s1.twoSum(nums, 6) == vector<int>({1, 2}));
        REQUIRE(s2.twoSum(nums, 6) == vector<int>({1, 2}));
        REQUIRE(s3.twoSum(nums, 6) == vector<int>({1, 2}));
    }

    SECTION("") {
        vector<int> nums = {3, 3};
        REQUIRE(s1.twoSum(nums, 6) == vector<int>({0, 1}));
        REQUIRE(s2.twoSum(nums, 6) == vector<int>({0, 1}));
        REQUIRE(s3.twoSum(nums, 6) == vector<int>({0, 1}));
    }
}
