#include <gtest/gtest.h>
#include "queue.h"
#include <string>
#include <stdexcept>

TEST(QueueTest, NewQueueIsEmpty) {
    Queue<int> q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.head, nullptr);
    EXPECT_EQ(q.tail, nullptr);
}

TEST(QueueTest, PushIncreasesSize) {
    Queue<int> q;
    q.push(10);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);
}

TEST(QueueTest, FifoOrder) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);

    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PopOnEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, FrontOnEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(QueueTest, BackOnEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, WorksWithStrings) {
    Queue<std::string> q;
    q.push("a");
    q.push("b");
    q.push("c");
    EXPECT_EQ(q.front(), "a");
    EXPECT_EQ(q.back(), "c");
    q.pop();
    EXPECT_EQ(q.front(), "b");
}

TEST(QueueTest, CopyConstructorDeepCopies) {
    Queue<int> a;
    a.push(1);
    a.push(2);

    Queue<int> b(a);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);

    b.pop();
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 1);
}

TEST(QueueTest, CopyAssignment) {
    Queue<int> a;
    a.push(1);
    a.push(2);

    Queue<int> b;
    b.push(99);
    b = a;

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);

    b.pop();
    EXPECT_EQ(a.size(), 2);
}

TEST(QueueTest, SelfAssignmentSafe) {
    Queue<int> a;
    a.push(5);
    a = a;
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a.front(), 5);
}

TEST(QueueTest, MoveConstructor) {
    Queue<int> a;
    a.push(1);
    a.push(2);

    Queue<int> b(std::move(a));
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);

    EXPECT_TRUE(a.isEmpty());
    EXPECT_EQ(a.size(), 0);
}

TEST(QueueTest, MoveAssignment) {
    Queue<int> a;
    a.push(1);
    a.push(2);

    Queue<int> b;
    b.push(99);
    b = std::move(a);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);
    EXPECT_TRUE(a.isEmpty());
}

TEST(QueueTest, StressManyOperations) {
    Queue<int> q;
    const int N = 1000;
    for (int i = 0; i < N; ++i) q.push(i);
    EXPECT_EQ(q.size(), static_cast<std::size_t>(N));

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
    EXPECT_TRUE(q.isEmpty());
}