/**
 * @file test_simple_state_pattern.c
 * @brief Simple tests for the new State Pattern implementation
 */

#include <unity.h>
#include "../src/Context/Context.h"
#include "../src/State/State.h"
#include "../src/mutex/Mutex.h"

// Global test variables
Context* context;
Mutex mutex;

// Test setup - called before each test
void setUp(void) {
    States_Init();
    context = Context_Create();
    Mutex_init(&mutex);
    Context_setMutex(context, &mutex);
}

// Test teardown - called after each test
void tearDown(void) {
    if (context != NULL) {
        Context_Destroy(context);
        context = NULL;
    }
    Mutex_destroy(&mutex);
}

// === BASIC FUNCTIONALITY TESTS ===

void test_digit_function(void) {
    TEST_ASSERT_EQUAL(0, digit('0'));
    TEST_ASSERT_EQUAL(5, digit('5'));
    TEST_ASSERT_EQUAL(9, digit('9'));
    TEST_ASSERT_EQUAL(-1, digit('a'));
    TEST_ASSERT_EQUAL(-1, digit('.'));
}

void test_context_creation(void) {
    TEST_ASSERT_NOT_NULL(context);
    TEST_ASSERT_NOT_NULL(Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context));
    TEST_ASSERT_EQUAL(0, Context_getFractionalDigits(context));
}

void test_simple_integer(void) {
    Context_processString(context, "123");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_simple_decimal(void) {
    Context_processString(context, "45.67");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_multiple_numbers(void) {
    Context_processString(context, "12 34 56");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_empty_string(void) {
    Context_processString(context, "");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_whitespace_only(void) {
    Context_processString(context, "   ");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_mixed_content(void) {
    Context_processString(context, "12.5 abc 34");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

// === INDIVIDUAL EVENT TESTS ===

void test_process_digit(void) {
    Context_processDigit(context, '5');
    TEST_ASSERT_EQUAL_DOUBLE(5.0, Context_getResult(context));
}

void test_process_dot(void) {
    Context_processDigit(context, '1');
    Context_processDot(context);
    Context_processDigit(context, '5');
    // Should have processed "1.5"
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_process_whitespace(void) {
    Context_processDigit(context, '1');
    Context_processWhiteSpace(context);
    // Should reset after whitespace
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context));
}

// === EDGE CASE TESTS ===

void test_leading_dot(void) {
    Context_processString(context, ".5");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_multiple_dots(void) {
    Context_processString(context, "1.2.3");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

void test_large_number(void) {
    Context_processString(context, "123456789");
    TEST_ASSERT_NOT_NULL(Context_getState(context));
}

// === MAIN TEST RUNNER ===

int main(void) {
    UNITY_BEGIN();
    
    // Basic functionality
    RUN_TEST(test_digit_function);
    RUN_TEST(test_context_creation);
    RUN_TEST(test_simple_integer);
    RUN_TEST(test_simple_decimal);
    RUN_TEST(test_multiple_numbers);
    RUN_TEST(test_empty_string);
    RUN_TEST(test_whitespace_only);
    RUN_TEST(test_mixed_content);
    
    // Individual events
    RUN_TEST(test_process_digit);
    RUN_TEST(test_process_dot);
    RUN_TEST(test_process_whitespace);
    
    // Edge cases
    RUN_TEST(test_leading_dot);
    RUN_TEST(test_multiple_dots);
    RUN_TEST(test_large_number);
    
    return UNITY_END();
}
