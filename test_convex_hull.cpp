#include <gtest/gtest.h>
#include "convex.h"

extern "C" {
#include "convex.h"  
}

bool areEqual(std::vector<Point> expected, Point result[], int size) {
    if (expected.size() != size) return false;
    for (size_t i = 0; i < expected.size(); i++) {
        if (expected[i].x != result[i].x || expected[i].y != result[i].y) {
            return false;
        }
    }
    return true;
}

TEST(ConvexHullTests, BasicHull) {
    Point points[] = { {0, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}, {2, 0} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    std::vector<Point> expected = { {0, 0}, {2, 0}, {2, 2}, {1, 3}, {0, 2} };

    ASSERT_TRUE(areEqual(expected, result, hullSize));
}

TEST(ConvexHullTests, NotEnoughPoints) {
    Point points[] = { {0, 0}, {1, 1} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    ASSERT_EQ(hullSize, 0);
}

TEST(ConvexHullTests, SinglePoint) {
    Point points[] = { {1, 1} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    std::vector<Point> expected = { {1, 1} };

    ASSERT_TRUE(areEqual(expected, result, hullSize));
}

TEST(ConvexHullTests, CollinearPoints) {
    Point points[] = { {0, 0}, {1, 1}, {2, 2}, {3, 3} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    std::vector<Point> expected = { {0, 0}, {3, 3} };

    ASSERT_TRUE(areEqual(expected, result, hullSize));
}

TEST(ConvexHullTests, CollinearWithExtraPoint) {
    Point points[] = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    std::vector<Point> expected = { {0, 0}, {3, 3}, {0, 3} };

    ASSERT_TRUE(areEqual(expected, result, hullSize));
}

TEST(ConvexHullTests, RandomPoints) {
    Point points[] = { {0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3}, {1, 2} };
    Point result[MAX_POINTS];
    int n = sizeof(points) / sizeof(points[0]);

    int hullSize = convexHull(points, n, result);
    std::vector<Point> expected = { {0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3} };

    ASSERT_TRUE(areEqual(expected, result, hullSize));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
