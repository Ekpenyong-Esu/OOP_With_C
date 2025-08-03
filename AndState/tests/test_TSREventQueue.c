#include <unity.h>
#include "../src/TSREventQueue/TSREventQueue.h"
#include "../src/TokenizeAsyncSinglePkg/TokenizeAsyncSinglePkg.h"

void setUp(void) {}
void tearDown(void) {}

void test_TSREventQueue_basic(void) {
    TSREventQueue queue;
    TSREventQueue_Init(&queue);
    TEST_ASSERT_TRUE(TSREventQueue_isEmpty(&queue));
    Event event;
    event.eType = EVDIGIT;
    event.ed.c = '5';
    TEST_ASSERT_TRUE(TSREventQueue_post(&queue, event));
    TEST_ASSERT_FALSE(TSREventQueue_isEmpty(&queue));
    Event pulled = TSREventQueue_pull(&queue);
    TEST_ASSERT_EQUAL(EVDIGIT, pulled.eType);
    TEST_ASSERT_EQUAL('5', pulled.ed.c);
    TEST_ASSERT_TRUE(TSREventQueue_isEmpty(&queue));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_TSREventQueue_basic);
    return UNITY_END();
}
