#include <stdio.h>
#include "EiTOS/src/include/schedulerQueue.hpp"
#include "gtest/gtest.h"


TEST(SchedulerQueueTest, SizeTest) {
	SchedulerQueue_t SchedulerQueue;
	EXPECT_EQ(SchedulerQueue.size(), 0);
	TaskStruct_t task1;
	task1.id = 0;
	task1.val = 1;
	SchedulerQueue.push(task1);
    EXPECT_EQ(SchedulerQueue.size(), 1);
    SchedulerQueue.push(task1);
    EXPECT_EQ(SchedulerQueue.size(), 2);
}

TEST(SchedulerQueueTest, diffVals) {
    SchedulerQueue_t SchedulerQueue;
    EXPECT_EQ(SchedulerQueue.size(), 0);
    TaskStruct_t task1;
    const int N = 10;
    for(int i = 0; i < N; ++i) {
        task1.id = i;
        task1.val = i;
        SchedulerQueue.push(task1);
    }
    EXPECT_EQ(SchedulerQueue.size(), N);
    for(int i = 0; i < N; ++i) {
        task1 = SchedulerQueue.front();
        SchedulerQueue.pop();
        EXPECT_EQ(task1.val, N-i-1);
        EXPECT_EQ(task1.id, N-i-1);
    }
}

TEST(SchedulerQueueTest, eqVals) {
    SchedulerQueue_t SchedulerQueue;
    EXPECT_EQ(SchedulerQueue.size(), 0);
    TaskStruct_t task1;
    for(int vall = 0; vall < 10; ++vall) {
        task1.val = vall;
        const int N = 10;
        for(int i = 0; i < N; ++i) {
            task1.id = i+vall;
            SchedulerQueue.push(task1);
        }
        EXPECT_EQ(SchedulerQueue.size(), N);
        for(int i = 0; i < N; ++i) {
            task1 = SchedulerQueue.front();
            SchedulerQueue.pop();
            EXPECT_EQ(task1.val, vall);
            EXPECT_EQ(task1.id, i+vall);
        }
        EXPECT_EQ(SchedulerQueue.size(), 0);
    }
}
