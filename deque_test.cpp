
#include "gtest/gtest.h"

extern "C" {
#include "../src/Deque.h"
}

TEST(DequeTest, EmptyInitially) {
    DequePtr deque = DequeInit();
    ASSERT_TRUE(DequeEmpty(deque));
    ASSERT_EQ(DequeSize(deque), 0u);
    DequeDestroy(deque);
}

TEST(DequeTest, AddRemoveFront) {
    DequePtr deque = DequeInit();
    int a = 1, b = 2;
    DequeAddFirst(deque, &a);
    EXPECT_FALSE(DequeEmpty(deque));
    EXPECT_EQ(DequeSize(deque), 1u);
    DequeAddFirst(deque, &b);
    EXPECT_EQ(DequeSize(deque), 2u);

    int* removed = (int*)DequeRemoveFirst(deque);
    EXPECT_EQ(*removed, b);
    EXPECT_EQ(DequeSize(deque), 1u);

    removed = (int*)DequeRemoveFirst(deque);
    EXPECT_EQ(*removed, a);
    EXPECT_TRUE(DequeEmpty(deque));

    DequeDestroy(deque);
}

TEST(DequeTest, AddRemoveLast) {
    DequePtr deque = DequeInit();
    int a = 1, b = 2;
    DequeAddLast(deque, &a);
    EXPECT_FALSE(DequeEmpty(deque));
    EXPECT_EQ(DequeSize(deque), 1u);
    DequeAddLast(deque, &b);
    EXPECT_EQ(DequeSize(deque), 2u);

    int* removed = (int*)DequeRemoveLast(deque);
    EXPECT_EQ(*removed, b);
    EXPECT_EQ(DequeSize(deque), 1u);

    removed = (int*)DequeRemoveLast(deque);
    EXPECT_EQ(*removed, a);
    EXPECT_TRUE(DequeEmpty(deque));

    DequeDestroy(deque);
}

TEST(DequeTest, MixedOperations) {
    DequePtr deque = DequeInit();
    int a = 1, b = 2, c = 3, d = 4;
    // Add to front: [a] Add to back:  [a, b] Add to front: [c, a, b] Add to back:  [c, a, b, d]
    DequeAddFirst(deque, &a);   // Deque: 1
    DequeAddLast(deque, &b);    // Deque: 1, 2
    DequeAddFirst(deque, &c);   // Deque: 3, 1, 2
    DequeAddLast(deque, &d);    // Deque: 3, 1, 2, 4
    ASSERT_EQ(DequeSize(deque), 4u);

    int* removed = (int*)DequeRemoveFirst(deque);
    EXPECT_EQ(*removed, c);      // Expect 3
    removed = (int*)DequeRemoveLast(deque);
    EXPECT_EQ(*removed, d);      // Expect 4
    EXPECT_EQ(DequeSize(deque), 2u);

    removed = (int*)DequeRemoveFirst(deque);
    EXPECT_EQ(*removed, a);      // Expect 1
    removed = (int*)DequeRemoveLast(deque);
    EXPECT_EQ(*removed, b);      // Expect 2
    EXPECT_TRUE(DequeEmpty(deque));

    DequeDestroy(deque);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

