#include "gtest/gtest.h"

extern "C" {
#include "RandomizedQueue.h"
}

TEST(RandomizedQueueTest, EmptyInitially) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 0u);
    RandomizedQueueDestroy(rq);
}

TEST(RandomizedQueueTest, EnqueueAndSize) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    int a = 10, b = 20, c = 30;
    RandomizedQueueEnqueue(rq, &a);
    EXPECT_FALSE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 1u);
    RandomizedQueueEnqueue(rq, &b);
    EXPECT_EQ(RandomizedQueueSize(rq), 2u);
    RandomizedQueueEnqueue(rq, &c);
    EXPECT_EQ(RandomizedQueueSize(rq), 3u);
    RandomizedQueueDestroy(rq);
}

TEST(RandomizedQueueTest, EnqueueDequeue) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    int a = 1, b = 2, c = 3, d = 4;
    RandomizedQueueEnqueue(rq, &a);
    RandomizedQueueEnqueue(rq, &b);
    RandomizedQueueEnqueue(rq, &c);
    RandomizedQueueEnqueue(rq, &d);
    EXPECT_EQ(RandomizedQueueSize(rq), 4u);

    bool seenA = false, seenB = false, seenC = false, seenD = false;
    for (int i = 0; i < 4; i++) {
        int* item = (int*)RandomizedQueueDequeue(rq);
        if (item == &a) seenA = true;
        else if (item == &b) seenB = true;
        else if (item == &c) seenC = true;
        else if (item == &d) seenD = true;
    }
    EXPECT_TRUE(seenA);
    EXPECT_TRUE(seenB);
    EXPECT_TRUE(seenC);
    EXPECT_TRUE(seenD);
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    RandomizedQueueDestroy(rq);
}

TEST(RandomizedQueueTest, DequeueEmptyReturnsNull) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    EXPECT_EQ(RandomizedQueueDequeue(rq), nullptr);
    RandomizedQueueDestroy(rq);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

