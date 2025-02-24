#include "dynamic_connectivity.h"

#include <gtest/gtest.h>

class DynamicConnectivityTest : public ::testing::Test {
protected:
    void SetUp() override {
        init_dynamic_connectivity(&co, 10);
    }

    void TearDown() override {
        for (int i = 0; i < CAPACITY; ++i) {
            co.id[i] = 0;
            co.sz[i] = 0;
        }
    }

    DynamicConnectivity co;
};

TEST_F(DynamicConnectivityTest, Initialization) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(co.id[i], i);
        EXPECT_EQ(co.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, InitializationCapacity) {
    init_dynamic_connectivity(&co, CAPACITY);
    for (int i = 0; i < CAPACITY; ++i) {
        EXPECT_EQ(co.id[i], i);
        EXPECT_EQ(co.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, RootFunction) {
    EXPECT_EQ(root(&co, 0), 0);
    EXPECT_EQ(root(&co, 1), 1);
    EXPECT_EQ(root(&co, 2), 2);
}

TEST_F(DynamicConnectivityTest, ConnectedFunction) {
    EXPECT_FALSE(connected(&co, 0, 1));
    EXPECT_TRUE(connected(&co, 0, 0));
}

TEST_F(DynamicConnectivityTest, UnionFunction) {
    add_union(&co, 0, 1);
    EXPECT_TRUE(connected(&co, 0, 1));
    EXPECT_TRUE(connected(&co, 1, 0));

    add_union(&co, 1, 2);
    EXPECT_TRUE(connected(&co, 0, 2));
}

TEST_F(DynamicConnectivityTest, TestTwoConnectedComponents) {
    add_union(&co, 4, 3);
    add_union(&co, 3, 8);
    add_union(&co, 6, 5);
    add_union(&co, 9, 4);
    add_union(&co, 2, 1);
    add_union(&co, 8, 9);
    add_union(&co, 5, 0);
    add_union(&co, 7, 2);
    add_union(&co, 6, 1);

    EXPECT_TRUE(connected(&co, 0, 7));
    EXPECT_TRUE(connected(&co, 3, 9));
    EXPECT_FALSE(connected(&co, 0, 3));
}

TEST_F(DynamicConnectivityTest, TestWeightedUnion) {
    add_union(&co, 4, 3);
    add_union(&co, 3, 8);
    add_union(&co, 6, 5);
    add_union(&co, 9, 4);

    int root_4 = root(&co, 4);
    int root_9 = root(&co, 9);

    ASSERT_EQ(root_4, root_9);
    ASSERT_EQ(root(&co, 3), root_4);
    ASSERT_EQ(root(&co, 8), root_4);
}

TEST_F(DynamicConnectivityTest, TestPathCompression) {
    add_union(&co, 4, 3);
    add_union(&co, 3, 8);
    add_union(&co, 6, 5);
    add_union(&co, 9, 4);
    add_union(&co, 2, 1);

    int root_3_before = root(&co, 3);
    int root_8_before = root(&co, 8);

    int root_3_after = root(&co, 3);
    int root_8_after = root(&co, 8);

    ASSERT_EQ(root_3_before, root_3_after);
    ASSERT_EQ(root_8_before, root_8_after);

    ASSERT_EQ(co.id[3], root_3_after);
    ASSERT_EQ(co.id[8], root_8_after);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

