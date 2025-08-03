#include <unity.h>
#include "TokenizeAsyncSinglePkg.h"
#include "TSREventQueue.h"
#include "TSRSyncSingleReceptor.h"
#include "Mutex.h"

#define EXPECTED_DIGIT_VALUE 7.0

void setUp(void) {
    // Initialize before each test
}

void tearDown(void) {
    // Clean up after each test
}

// Test the digit helper function
void test_digit_function_should_convert_character_to_number(void) {
    TEST_ASSERT_EQUAL(0, digit('0'));
    TEST_ASSERT_EQUAL(5, digit('5'));
    TEST_ASSERT_EQUAL(9, digit('9'));
}

// Test single receptor creation and initialization
void test_single_receptor_should_initialize_correctly(void) {
    TokenizerSyncSingleReceptor* receptor = TokenizerSyncSingleReceptor_Create();
    TEST_ASSERT_NOT_NULL(receptor);
    TEST_ASSERT_EQUAL(0.0, receptor->result);
    TEST_ASSERT_EQUAL(NONUMBER_STATE, receptor->stateID);
    TEST_ASSERT_EQUAL(NULL_SSTATE, receptor->subStateID);
    TokenizerSyncSingleReceptor_Destroy(receptor);
}

// Test event queue basic functionality
void test_event_queue_should_handle_basic_operations(void) {
    TSREventQueue queue;
    TSREventQueue_Init(&queue);

    TEST_ASSERT_TRUE(TSREventQueue_isEmpty(&queue));
    TEST_ASSERT_FALSE(TSREventQueue_isFull(&queue));

    // Test posting an event
    Event event;
    event.eType = EVDIGIT;
    event.ed.c = '5';
    TEST_ASSERT_TRUE(TSREventQueue_post(&queue, event));
    TEST_ASSERT_FALSE(TSREventQueue_isEmpty(&queue));

    // Test pulling an event
    Event pulled = TSREventQueue_pull(&queue);
    TEST_ASSERT_EQUAL(EVDIGIT, pulled.eType);
    TEST_ASSERT_EQUAL('5', pulled.ed.c);
    TEST_ASSERT_TRUE(TSREventQueue_isEmpty(&queue));
}

// Test single receptor pattern: only one receptor processes events sequentially
void test_single_receptor_pattern_should_process_digit_events(void) {
    // Create the single receptor (key aspect of the pattern)
    TokenizerSyncSingleReceptor* receptor = TokenizerSyncSingleReceptor_Create();

    // Create event for digit '7'
    Event event;
    event.eType = EVDIGIT;
    event.ed.c = '7';

    // Process the event through the single receptor
    TokenizerSyncSingleReceptor_eventDispatch(receptor, event);

    // Verify the receptor processed the event correctly
    TEST_ASSERT_EQUAL(EXPECTED_DIGIT_VALUE, receptor->result);
    TEST_ASSERT_EQUAL(GOTNUMBER_STATE, receptor->stateID);
    TEST_ASSERT_EQUAL(PROCESSINGWHOLEPART_SSTATE, receptor->subStateID);

    TokenizerSyncSingleReceptor_Destroy(receptor);
}

// Test mutex functionality
void test_mutex_should_initialize_and_work_correctly(void) {
    Mutex mutex;

    // Test initialization
    TEST_ASSERT_EQUAL(0, Mutex_init(&mutex));

    // Test locking and unlocking
    TEST_ASSERT_EQUAL(0, Mutex_lock(&mutex));
    TEST_ASSERT_EQUAL(0, Mutex_release(&mutex));

    // Test trylock
    TEST_ASSERT_EQUAL(0, Mutex_trylock(&mutex));
    TEST_ASSERT_EQUAL(0, Mutex_release(&mutex));

    // Test destruction
    TEST_ASSERT_EQUAL(0, Mutex_destroy(&mutex));
}

int main(void) {
    UNITY_BEGIN();

    // Test basic utilities
    RUN_TEST(test_digit_function_should_convert_character_to_number);

    // Test mutex functionality
    RUN_TEST(test_mutex_should_initialize_and_work_correctly);

    // Test single receptor pattern implementation
    RUN_TEST(test_single_receptor_should_initialize_correctly);
    RUN_TEST(test_event_queue_should_handle_basic_operations);
    RUN_TEST(test_single_receptor_pattern_should_process_digit_events);

    return UNITY_END();
}
