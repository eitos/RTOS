#include <stdio.h>
#include <swapTable.hpp>
#include "gtest/gtest.h"

TEST(swapTableTest, testSize) {
    SwapTable_t<int, 100> Q;
    EXPECT_EQ(Q.size(), 0);
    for ( int i = 0; i < 100; ++i ) {
        Q.add(i);
        EXPECT_EQ(Q.size(), i+1);
    }
}

TEST(swapTableTest, testOrder) {
    SwapTable_t<int, 100> Q;
    EXPECT_EQ(Q.size(), 0);
    for ( int i = 0; i < 100; ++i ) {
        Q.add(i);
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 0; i < 100; ++i ) {
        Q[i] = i;
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 99; i >= 0; --i ) {
        Q.remove(0);
        EXPECT_EQ(Q.size(), i);
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(swapTableTest, removing) {
    SwapTable_t<int, 100> Q;
    EXPECT_EQ(Q.size(), 0);
    for ( int i = 0; i < 100; ++i ) {
        Q.add(i);
    }
    EXPECT_EQ(Q.size(), 100);
    Q.remove(0);
    for ( int i = 99; i >= 1; --i ) {
        EXPECT_EQ(Q[0], i);
        Q.remove(0);
        EXPECT_EQ(Q.size(), i-1);
    }
    EXPECT_EQ(Q.size(), 0);
}

struct test1 {
    int val;
    int id;
    bool operator<(const test1& second) {
        return (this->val < second.val);
    }
};

TEST(swapTableTest, testStruct1) {
    SwapTable_t<test1, 100> Q;
    test1 x;
    EXPECT_EQ(Q.size(), 0);
    for ( int i = 0; i < 100; ++i ) {
        x.val = i;
        x.id = i;
        Q.add(x);
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 0; i < 100; ++i ) {
        EXPECT_EQ(Q[i].val, i);
        EXPECT_EQ(Q[i].id, i);
    }
    for ( int i = 99; i >= 0; --i ) {
        EXPECT_EQ(Q[i].val, i);
        EXPECT_EQ(Q[i].id, i);
        Q.remove(i);
        EXPECT_EQ(Q.size(), i);
    }
    EXPECT_EQ(Q.size(), 0);
}
