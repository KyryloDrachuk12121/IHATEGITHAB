#include <gtest/gtest.h>

extern void initialize_weighted_quick_union();
extern int root__quick_union_path_compression(int* id, int i);
extern bool connected__quick_union(int* id, int p, int q);
extern void union__weighted_quick_union(int* id, int p, int q);
extern int root__quick_union(const int* id, int i);
extern bool connected__quick_find(const int* id, int p, int q);
extern void union__quick_find(int* id, int p, int q);

extern int sz[];
#define N 10

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }
};

TEST_F(QuickUnionTest, ConnectedQuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, UnionQuickFind) {
    union__quick_find(id, 2, 5);
    EXPECT_TRUE(connected__quick_find(id, 2, 5));
}

TEST_F(QuickUnionTest, UnionQuickUnion) {
    union__weighted_quick_union(id, 1, 2);
    EXPECT_TRUE(connected__quick_union(id, 1, 2));
}

TEST_F(QuickUnionTest, RootQuickUnion) {
    EXPECT_EQ(root__quick_union(id, 4), 4);
    union__weighted_quick_union(id, 4, 5);
    EXPECT_EQ(root__quick_union(id, 5), root__quick_union(id, 4));
}

TEST_F(QuickUnionTest, RootQuickUnionPathCompression) {
    union__weighted_quick_union(id, 6, 7);
    union__weighted_quick_union(id, 7, 8);
    int root_8_before = root__quick_union(id, 8);
    root__quick_union_path_compression(id, 8);
    int root_8_after = root__quick_union(id, 8);
    EXPECT_EQ(root_8_before, root_8_after);
}

TEST_F(QuickUnionTest, UnionWeightedQuickUnion) {
    union__weighted_quick_union(id, 0, 9);
    union__weighted_quick_union(id, 9, 3);
    EXPECT_TRUE(connected__quick_union(id, 0, 3));
}




