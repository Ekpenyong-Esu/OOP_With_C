/**
 * @file test_tokenizer_basic.c
 * @brief SIMPLIFIED Basic tests for the clean tokenizer implementation
 * 
 * These tests are designed to be easy to understand and verify that our
 * simplified tokenizer works correctly with basic number parsing.
 */

#include <unity.h>
#include "../src/TokenizerStateTable/TokenizerStateTable.h"

// Global tokenizer for tests
NumberTokenizer* tokenizer;

void setUp(void) {
    tokenizer = create_tokenizer();
    TEST_ASSERT_NOT_NULL(tokenizer);
}

void tearDown(void) {
    destroy_tokenizer(tokenizer);
    tokenizer = NULL;
}

// === BASIC FUNCTIONALITY TESTS ===

void test_char_to_digit_function(void) {
    TEST_ASSERT_EQUAL(0, char_to_digit('0'));
    TEST_ASSERT_EQUAL(5, char_to_digit('5'));
    TEST_ASSERT_EQUAL(9, char_to_digit('9'));
    TEST_ASSERT_EQUAL(-1, char_to_digit('a')); // Invalid character
}

void test_tokenizer_initialization(void) {
    TEST_ASSERT_NOT_NULL(tokenizer);
    TEST_ASSERT_EQUAL(0.0, tokenizer->result);
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    TEST_ASSERT_EQUAL(10.0, tokenizer->decimalPlace);
}

void test_simple_digit_processing(void) {
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    TEST_ASSERT_EQUAL(5.0, tokenizer->result);
}

void test_multiple_digits(void) {
    process_character(tokenizer, '1');
    process_character(tokenizer, '2');
    process_character(tokenizer, '3');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    TEST_ASSERT_EQUAL(123.0, tokenizer->result);
}

void test_simple_decimal_processing(void) {
    process_string(tokenizer, "3.14");
    // After processing complete string, should be back to WAITING
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    // Result gets reset after finishing number
    TEST_ASSERT_EQUAL(0.0, tokenizer->result);
}

void test_decimal_starting_with_dot(void) {
    process_character(tokenizer, '.');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
    process_character(tokenizer, '7');
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
}

void test_multiple_numbers_in_sequence(void) {
    process_string(tokenizer, "12 34");
    // Should end in WAITING state after processing both numbers
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    TEST_ASSERT_EQUAL(0.0, tokenizer->result); // Reset after finishing
}

// === UTILITY FUNCTION TESTS ===

void test_state_string_conversion(void) {
    TEST_ASSERT_EQUAL_STRING("WAITING", state_to_string(STATE_WAITING));
    TEST_ASSERT_EQUAL_STRING("WHOLE", state_to_string(STATE_WHOLE));
    TEST_ASSERT_EQUAL_STRING("DECIMAL", state_to_string(STATE_DECIMAL));
}

void test_event_string_conversion(void) {
    TEST_ASSERT_EQUAL_STRING("DIGIT", event_to_string(EVENT_DIGIT));
    TEST_ASSERT_EQUAL_STRING("DOT", event_to_string(EVENT_DOT));
    TEST_ASSERT_EQUAL_STRING("SPACE", event_to_string(EVENT_SPACE));
    TEST_ASSERT_EQUAL_STRING("END", event_to_string(EVENT_END));
}

// === ERROR HANDLING TESTS ===

void test_null_tokenizer_handling(void) {
    // These should not crash
    process_character(NULL, '5');
    process_string(NULL, "123");
    print_tokenizer_state(NULL);
    destroy_tokenizer(NULL);
}

// === MAIN TEST RUNNER ===

int main(void) {
    UNITY_BEGIN();
    
    // Basic functionality
    RUN_TEST(test_char_to_digit_function);
    RUN_TEST(test_tokenizer_initialization);
    RUN_TEST(test_simple_digit_processing);
    RUN_TEST(test_multiple_digits);
    
    // Decimal processing
    RUN_TEST(test_simple_decimal_processing);
    RUN_TEST(test_decimal_starting_with_dot);
    
    // Multiple numbers
    RUN_TEST(test_multiple_numbers_in_sequence);
    
    // Utility functions
    RUN_TEST(test_state_string_conversion);
    RUN_TEST(test_event_string_conversion);
    
    // Error handling
    RUN_TEST(test_null_tokenizer_handling);
    
    return UNITY_END();
}
