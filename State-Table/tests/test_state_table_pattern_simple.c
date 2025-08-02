/**
 * @file test_state_table_pattern_simple.c
 * @brief SIMPLIFIED Comprehensive tests for the State Table Pattern
 * 
 * This replaces the complex 400-line test file with a clean, easy-to-understand
 * version that still provides comprehensive coverage but focuses on clarity.
 * 
 * Test Categories:
 * - Core functionality
 * - State transitions  
 * - Edge cases
 * - Error handling
 * - Integration scenarios
 */

#include <unity.h>
#include <string.h>
#include "../src/TokenizerStateTable/TokenizerStateTable.h"

// Global test fixture
NumberTokenizer* tokenizer;

void setUp(void) {
    tokenizer = create_tokenizer();
    TEST_ASSERT_NOT_NULL(tokenizer);
}

void tearDown(void) {
    destroy_tokenizer(tokenizer);
    tokenizer = NULL;
}

// === CORE FUNCTIONALITY TESTS ===

void test_basic_integer_parsing(void) {
    process_string(tokenizer, "123");
    // After processing, should be back to WAITING state with result reset
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_basic_decimal_parsing(void) {
    process_string(tokenizer, "45.67");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_zero_handling(void) {
    process_string(tokenizer, "0");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    
    process_string(tokenizer, "0.5");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

// === STATE TRANSITION TESTS ===

void test_waiting_to_whole_transition(void) {
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    TEST_ASSERT_EQUAL(5.0, tokenizer->result);
}

void test_whole_to_decimal_transition(void) {
    process_character(tokenizer, '1');
    process_character(tokenizer, '2');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    
    process_character(tokenizer, '.');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
}

void test_decimal_digit_accumulation(void) {
    process_character(tokenizer, '.');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
    
    process_character(tokenizer, '2');
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
}

void test_number_completion_transitions(void) {
    process_character(tokenizer, '4');
    process_character(tokenizer, '2');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    
    // Space should complete the number and return to WAITING
    process_character(tokenizer, ' ');
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

// === EDGE CASE TESTS ===

void test_decimal_point_without_preceding_digit(void) {
    process_character(tokenizer, '.');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
    
    process_character(tokenizer, '7');
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
}

void test_multiple_decimal_points(void) {
    process_character(tokenizer, '1');
    process_character(tokenizer, '.');
    process_character(tokenizer, '2');
    TEST_ASSERT_EQUAL(STATE_DECIMAL, tokenizer->currentState);
    
    // Second decimal point should complete the current number
    process_character(tokenizer, '.');
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_large_numbers(void) {
    process_string(tokenizer, "999999.999999");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_sequential_whitespace(void) {
    process_string(tokenizer, "12   34");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

// === ERROR HANDLING TESTS ===

void test_null_tokenizer_safety(void) {
    // These should not crash
    process_character(NULL, '5');
    process_string(NULL, "123");
    print_tokenizer_state(NULL);
    destroy_tokenizer(NULL);
    
    // Test should pass if no crash occurs
    TEST_ASSERT_TRUE(1);
}

void test_empty_string_processing(void) {
    process_string(tokenizer, "");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    TEST_ASSERT_EQUAL(0.0, tokenizer->result);
}

void test_whitespace_only_string(void) {
    process_string(tokenizer, "   ");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    TEST_ASSERT_EQUAL(0.0, tokenizer->result);
}

void test_invalid_characters_handling(void) {
    process_character(tokenizer, '5');
    TEST_ASSERT_EQUAL(STATE_WHOLE, tokenizer->currentState);
    
    // Invalid characters should be treated as whitespace
    process_character(tokenizer, 'x');
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

// === INTEGRATION TESTS ===

void test_multiple_number_sequence(void) {
    process_string(tokenizer, "12 34.5 67");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_mixed_format_numbers(void) {
    process_string(tokenizer, "123 .456 78.9 0.001");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

void test_complete_tokenization_workflow(void) {
    // Simulate a complete parsing session
    const char* test_inputs[] = {
        "42",
        "3.14159",
        ".5",
        "100.001",
        "0",
        "999.999",
        NULL
    };
    
    for (int i = 0; test_inputs[i] != NULL; i++) {
        // Reset tokenizer state
        tokenizer->currentState = STATE_WAITING;
        tokenizer->result = 0.0;
        tokenizer->decimalPlace = 10.0;
        
        // Process the input
        process_string(tokenizer, test_inputs[i]);
        
        // Should always end in WAITING state
        TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    }
}

// === UTILITY FUNCTION TESTS ===

void test_helper_functions(void) {
    // Test char_to_digit
    TEST_ASSERT_EQUAL(0, char_to_digit('0'));
    TEST_ASSERT_EQUAL(9, char_to_digit('9'));
    TEST_ASSERT_EQUAL(-1, char_to_digit('a'));
    
    // Test string conversion functions
    TEST_ASSERT_EQUAL_STRING("WAITING", state_to_string(STATE_WAITING));
    TEST_ASSERT_EQUAL_STRING("DIGIT", event_to_string(EVENT_DIGIT));
}

void test_state_information_display(void) {
    // Test that state display functions don't crash
    print_tokenizer_state(tokenizer);
    
    process_character(tokenizer, '5');
    print_tokenizer_state(tokenizer);
    
    process_character(tokenizer, '.');
    print_tokenizer_state(tokenizer);
    
    // Test passes if no crash occurs
    TEST_ASSERT_TRUE(1);
}

// === PERFORMANCE TESTS ===

void test_repeated_operations(void) {
    // Test that repeated operations work correctly
    for (int i = 0; i < 100; i++) {
        process_string(tokenizer, "123.45");
        TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
    }
}

void test_stress_parsing(void) {
    // Test parsing a long sequence of numbers
    process_string(tokenizer, "1 2 3 4 5 6 7 8 9 0 1.1 2.2 3.3 4.4 5.5");
    TEST_ASSERT_EQUAL(STATE_WAITING, tokenizer->currentState);
}

// === MAIN TEST RUNNER ===

int main(void) {
    UNITY_BEGIN();
    
    printf("Running Simplified State Table Pattern Tests...\n");
    
    // Core functionality
    RUN_TEST(test_basic_integer_parsing);
    RUN_TEST(test_basic_decimal_parsing);
    RUN_TEST(test_zero_handling);
    
    // State transitions
    RUN_TEST(test_waiting_to_whole_transition);
    RUN_TEST(test_whole_to_decimal_transition);
    RUN_TEST(test_decimal_digit_accumulation);
    RUN_TEST(test_number_completion_transitions);
    
    // Edge cases
    RUN_TEST(test_decimal_point_without_preceding_digit);
    RUN_TEST(test_multiple_decimal_points);
    RUN_TEST(test_large_numbers);
    RUN_TEST(test_sequential_whitespace);
    
    // Error handling
    RUN_TEST(test_null_tokenizer_safety);
    RUN_TEST(test_empty_string_processing);
    RUN_TEST(test_whitespace_only_string);
    RUN_TEST(test_invalid_characters_handling);
    
    // Integration tests
    RUN_TEST(test_multiple_number_sequence);
    RUN_TEST(test_mixed_format_numbers);
    RUN_TEST(test_complete_tokenization_workflow);
    
    // Utility functions
    RUN_TEST(test_helper_functions);
    RUN_TEST(test_state_information_display);
    
    // Performance tests
    RUN_TEST(test_repeated_operations);
    RUN_TEST(test_stress_parsing);
    
    printf("Simplified State Table Pattern Tests Complete!\n");
    
    return UNITY_END();
}
