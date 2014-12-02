#include <stdio.h>
#include <priorityQueue.hpp>
#include <task.hpp>
#include "gtest/gtest.h"

TEST(PriorityQueueTest, ints) {
    PriorityQueue_t<int, 10> Q;
    EXPECT_EQ(Q.size(), 0);
    for ( int i = 0; i < 10; ++i ) {
        Q.push(i);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 9; i >= 0; --i ) {
        const int & t = Q.front();
        EXPECT_EQ(t, i);
        Q.pop();
    }
    EXPECT_EQ(Q.size(), 0);
}

struct test1 {
    int val;
    bool operator<(const test1 & two) const {
      return (this->val < two.val);
    }
};

TEST(PriorityQueueTest, test1) {
    PriorityQueue_t<test1, 10> Q;
    test1 elem;
    for ( int i = 0; i < 10; ++i ) {
      elem.val = i;
      Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 9; i >= 0; --i ) {
        const test1 & t = Q.front();
        EXPECT_EQ(t.val, i);
        Q.pop();
    }
    EXPECT_EQ(Q.size(), 0);
}

struct test2 {
    int val;
    bool operator<(const test2 & two) const {
      return (this->val >= two.val);
    }
};

TEST(PriorityQueueTest, test2) {
    PriorityQueue_t<test2, 10> Q;
    test2 elem;
    for ( int i = 0; i < 10; ++i ) {
      elem.val = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 0; i < 10; ++i ) {
        const test2 & t = Q.front();
        EXPECT_EQ(t.val, i);
        Q.pop();
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, test2Diff) {
    PriorityQueue_t<test2, 20> Q;
    EXPECT_EQ(Q.size(), 0);
    test2 elem;
    for ( int i = 0; i < 10; ++i ) {
      elem.val = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 9; i >= 0; --i ) {
      elem.val = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 20);
    for ( int i = 0; i < 10; ++i ) {
      for ( int j = 0; j < 2; ++j ) {
          const test2 & t = Q.front();
          EXPECT_EQ(t.val, i);
          Q.pop();
      }
    }
    EXPECT_EQ(Q.size(), 0);
}

struct test3 {
    int val, id;
    bool operator<(const test3 & two) const {
      return (this->val < two.val);
    }
};

TEST(PriorityQueueTest, test3) {
    PriorityQueue_t<test3, 10> Q;
    test3 elem;
    for ( int i = 0; i < 10; ++i ) {
        elem.id = i;
        elem.val = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 9; i >= 0; --i ) {
        const test3 & t = Q.front();
        EXPECT_EQ(t.val, i);
        EXPECT_EQ(t.id, i);
        Q.pop();
    }
  EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, test3smallSameVals) {
    PriorityQueue_t<test3, 100> Q;
    test3 elem;
    elem.val = 1;
    for ( int i = 0; i < 10; ++i ) {
        elem.id = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 10);
    for ( int i = 0; i < 10; ++i ) {
        const test3 & t = Q.front();
        EXPECT_EQ(t.val, 1);
        EXPECT_EQ(t.id, i);
        Q.pop();
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, test3diffVals) {
    PriorityQueue_t<test3, 100> Q;
    test3 elem;
    for ( int i = 0; i < 10; ++i ) {
        for ( int j = 0; j < 10; ++j ) {
            elem.id = i;
            elem.val = j;
            Q.push(elem);
        }
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 9; i >= 0; --i ) {
        for ( int j = 0; j < 10; ++j ) {
            const test3 & t = Q.front();
            EXPECT_EQ(t.val, i);
            EXPECT_EQ(t.id, j);
            Q.pop();
        }
    }
    EXPECT_EQ(Q.size(), 0);
}


TEST(PriorityQueueTest, TaskStruct) {
    PriorityQueue_t<TaskStruct_t, 100> Q;
    TaskStruct_t elem;
    elem.blockingMutexNr = 0;
    for ( int i = 0; i < 10; ++i ) {
        for ( int j = 0; j < 10; ++j ) {
            Q.push(elem);
        }
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 9; i >= 0; --i ) {
        for ( int j = 0; j < 10; ++j ) {
            const TaskStruct_t & t = Q.front();
            Q.pop();
      }
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, TaskStructMutex) {
    PriorityQueue_t<TaskStruct_t, 100> Q;
    TaskStruct_t elem;
    for ( int i = 0; i < 10; ++i ) {
        elem.blockingMutexNr = i;
        for ( int j = 0; j < 10; ++j ) {
            elem.priority = j;
            Q.push(elem);
        }
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 0; i < 10; ++i ) {
        for ( int j = 9; j >= 0; --j ) {
            const TaskStruct_t & t = Q.front();
            EXPECT_EQ(t.priority, j);
            EXPECT_EQ(t.blockingMutexNr, i);
            Q.pop();
        }
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, TaskStructEqualNorm) {
    PriorityQueue_t<TaskStruct_t, 100> Q;
    TaskStruct_t elem;
    elem.blockingMutexNr = elem.priority = 0;
    for ( int i = 0; i < 100; ++i ) {
        elem.lowLevel.Stack = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 0; i < 100; ++i ) {
        const TaskStruct_t & t = Q.front();
        EXPECT_EQ(t.priority, 0);
        EXPECT_EQ(t.blockingMutexNr, 0);
        EXPECT_EQ(t.lowLevel.Stack, i);
        Q.pop();
    }
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, TaskStructOperatorBrace) {
    PriorityQueue_t<TaskStruct_t, 54> Q;
    TaskStruct_t elem;
    for ( int i = 0; i < 3; ++i ) {
        elem.blockingMutexNr = i;
        for ( int j = 0; j < 3; ++j ) {
            elem.priority = j;
            for ( int k = 0; k < 3; ++k ) {
                elem.lowLevel.Stack = k;
                Q.push(elem);
            }
        }
    }
    for ( int i = 2; i >= 0; --i ) {
        elem.blockingMutexNr = i;
        for ( int j = 2; j >= 0; --j ) {
            elem.priority = j;
            for ( int k = 0; k < 3; ++k ) {
                elem.lowLevel.Stack = k;
                Q.push(elem);
            }
        }
    }
    EXPECT_EQ(Q.size(), 54);
    int index = 0;
    for ( int i = 0; i < 3; ++i ) {
        for ( int j = 0; j < 3; ++j ) {
            for ( int n = 0; n < 2; ++n ) {
                for ( int k = 0; k < 3; ++k ) {
                    elem = Q[index++];
                    EXPECT_EQ(elem.blockingMutexNr, 2-i);
                    EXPECT_EQ(elem.priority, j);
                    EXPECT_EQ(elem.lowLevel.Stack, 2-k);
                }
            }
        }
    }
    EXPECT_EQ(Q.size(), 54);
    while (Q.size() > 0) Q.pop();
    EXPECT_EQ(Q.size(), 0);
}

TEST(PriorityQueueTest, TaskStructRemoval) {
    PriorityQueue_t<TaskStruct_t, 100> Q;
    TaskStruct_t elem;
    elem.blockingMutexNr = elem.priority = 0;
    for ( int i = 0; i < 100; ++i ) {
        elem.lowLevel.Stack = i;
        Q.push(elem);
    }
    EXPECT_EQ(Q.size(), 100);
    for ( int i = 0; i < 99; ++i ) {
        const TaskStruct_t & t = Q[0];
        TaskStruct_t t2 = Q[0];
        EXPECT_EQ(Q[0].priority, 0);
        EXPECT_EQ(Q[0].blockingMutexNr, 0);
        EXPECT_EQ(Q[0].lowLevel.Stack, 99-i);

        EXPECT_EQ(t.priority, 0);
        EXPECT_EQ(t.blockingMutexNr, 0);
        EXPECT_EQ(t.lowLevel.Stack, 99-i);

        EXPECT_EQ(t2.priority, 0);
        EXPECT_EQ(t2.blockingMutexNr, 0);
        EXPECT_EQ(t2.lowLevel.Stack, 99-i);

        Q.remove(0);
        TaskStruct_t t3 = Q[0];
        Q.remove(0);
        Q.push(t3);
        Q.push(t2);

        EXPECT_EQ(Q[0].priority, 0);
        EXPECT_EQ(Q[0].blockingMutexNr, 0);
        EXPECT_EQ(Q[0].lowLevel.Stack, 99-i);

        EXPECT_EQ(t.priority, 0);
        EXPECT_EQ(t.blockingMutexNr, 0);
        EXPECT_EQ(t.lowLevel.Stack, 99-i);

        EXPECT_EQ(t2.priority, 0);
        EXPECT_EQ(t2.blockingMutexNr, 0);
        EXPECT_EQ(t2.lowLevel.Stack, 99-i);
        Q.remove(0);
    }
    EXPECT_EQ(Q.size(), 1);
    Q.remove(0);
    EXPECT_EQ(Q.size(), 0);
}
