/**
 * @file test_integration.c
 * @brief Integration tests for the complete State Pattern workflow
 * 
 * This file tests the entire system working together:
 * Context + States + Mutex to parse numbers correctly.
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

// === INTEGRATION TESTS ===

void test_parse_integer_sequence(void) {
    Context_processString(context, "123");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context)); // Reset after completion
}

void test_parse_decimal_sequence(void) {
    Context_processString(context, "45.67");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context)); // Reset after completion
}

void test_parse_multiple_numbers(void) {
    Context_processString(context, "12 34 56");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context)); // Reset after completion
}

void test_parse_mixed_numbers(void) {
    Context_processString(context, "1.5 23 4.78");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context)); // Reset after completion
}

void test_edge_cases(void) {
    // Test empty string
    Context_processString(context, "");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    
    // Test only whitespace
    Context_processString(context, "   ");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    
    // Test only dots
    Context_processString(context, "...");
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
}

void test_state_transitions_manually(void) {
    // Start in NoNumber state
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    
    // Add a digit - should transition to ProcessingWhole
    Context_processDigit(context, '5');
    TEST_ASSERT_EQUAL_PTR(ProcessingWholeState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(5.0, Context_getResult(context));
    
    // Add a dot - should transition to ProcessingFraction
    Context_processDot(context);
    TEST_ASSERT_EQUAL_PTR(ProcessingFractionState, Context_getState(context));
    
    // Add fractional digit
    Context_processDigit(context, '2');
    TEST_ASSERT_EQUAL_PTR(ProcessingFractionState, Context_getState(context));
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 5.2, Context_getResult(context));
    
    // End with whitespace - should return to NoNumber
    Context_processWhiteSpace(context);
    TEST_ASSERT_EQUAL_PTR(NoNumberState, Context_getState(context));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, Context_getResult(context)); // Reset
}

// === MAIN TEST RUNNER ===

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_parse_integer_sequence);
    RUN_TEST(test_parse_decimal_sequence);
    RUN_TEST(test_parse_multiple_numbers);
    RUN_TEST(test_parse_mixed_numbers);
    RUN_TEST(test_edge_cases);
    RUN_TEST(test_state_transitions_manually);
    
    return UNITY_END();
}
