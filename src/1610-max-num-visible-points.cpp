/**
 * 1610. Maximum Number of Visible Points
 * https://leetcode.com/problems/maximum-number-of-visible-points/
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

/**
 * n: length of
 * Time: O()
 * Space: O()
 */
class Solution {
public:
    int visiblePoints(vector<vector<int>> &points,
                      int angle,
                      vector<int> &location) {
        vector<double> pointAngles; // degrees
        int alwaysVisible = 0;

        for (const auto &point : points) {
            // x tan(theta) = y
            // pi = 180 degrees
            if (point[0] == location[0]) {
                if (point[1] == location[1]) {
                    ++alwaysVisible;
                } else {
                    // 90 or 270 degrees
                    double angle = point[1] - location[1] > 0 ? 90 : 270;
                    pointAngles.push_back(angle);
                    pointAngles.push_back(angle + 360);
                }
            } else {
                double angle = atan(double(point[1] - location[1]) /
                                    double(point[0] - location[0])) *
                               180 / M_PI;
                if (angle < 0) {
                    angle += 360;
                }
                pointAngles.push_back(angle);
                pointAngles.push_back(angle + 360);
            }
        }

        if (pointAngles.empty()) {
            return alwaysVisible;
        }

        sort(pointAngles.begin(), pointAngles.end());

        for (auto ang : pointAngles) {
            cout << ang << " ";
        }
        cout << endl;

        int maxPoints = 0;
        size_t j = 0;

        for (size_t i = 0; i < pointAngles.size() / 2; ++i) {
            // size_t j = i;

            while (j < pointAngles.size() &&
                   pointAngles[j] - pointAngles[i] <= angle) {
                ++j;
            }

            cout << i << " -- " << j << endl;
            maxPoints = max(maxPoints, int(j - i));
        }

        return maxPoints + alwaysVisible;
    }
};

TEST_CASE("Title") {
    Solution s;

    SECTION("") {
        vector<vector<int>> points = {
            {45,  26},
            {82,  12},
            {33,  83},
            {58,  50},
            {55,  92},
            {66,  42},
            {25,  74},
            {74,  74},
            {36,  87},
            {7,   41},
            {89,  36},
            {44,  22},
            {84,  9 },
            {96,  90},
            {75,  51},
            {87,  15},
            {50,  75},
            {90,  84},
            {56,  18},
            {43,  48},
            {23,  27},
            {100, 34}
        };
        vector<int> loc = {32, 37};
        REQUIRE(s.visiblePoints(points, 12, loc) == 4);
    }
}
