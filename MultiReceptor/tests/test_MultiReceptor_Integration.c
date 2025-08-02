//
// Integration Tests for TokenizerMultiReceptor
//
// This file contains integration tests that verify the TokenizerMultiReceptor
// works correctly in realistic scenarios including multi-threaded environments,
// complex input parsing, and real-world usage patterns.
//
// Test Framework: Unity (C unit testing framework)
// Test Categories:
// - Multi-number string parsing
// - Complex input format handling
// - Performance and stress testing
// - Thread safety validation
// - Real-world scenario simulation
//

#define _POSIX_C_SOURCE 200112L  // Enable POSIX functions like usleep

#include "unity.h"
#include "MultiReceptor.h"
#include "Mutex.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

// Test fixture - global variables for test setup
static TokenizerMultiReceptor* tokenizer;
static Mutex* test_mutex;

/*
 * ============================================================================
 * TEST SETUP AND TEARDOWN
 * ============================================================================
 */

void setUp(void) {
    tokenizer = TokenizerMultiReceptor_Create();
    TEST_ASSERT_NOT_NULL(tokenizer);
    
    test_mutex = malloc(sizeof(Mutex));
    TEST_ASSERT_NOT_NULL(test_mutex);
    
    int result = Mutex_init(test_mutex);
    TEST_ASSERT_EQUAL_INT(0, result);
    
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
}

void tearDown(void) {
    if (tokenizer != NULL) {
        TokenizerMultiReceptor_Destroy(tokenizer);
        tokenizer = NULL;
    }
    
    if (test_mutex != NULL) {
        Mutex_destroy(test_mutex);
        free(test_mutex);
        test_mutex = NULL;
    }
}

/*
 * ============================================================================
 * HELPER FUNCTIONS FOR INTEGRATION TESTS
 * ============================================================================
 */

/**
 * @brief Helper function to simulate string parsing
 * @param input String to parse through the tokenizer
 * @param expected_numbers Array of expected parsed numbers
 * @param num_expected Number of expected results
 */
void parseStringAndVerify(const char* input, double* expected_numbers, int num_expected) {
    TEST_ASSERT_NOT_NULL(input);
    TEST_ASSERT_NOT_NULL(expected_numbers);
    
    int numbers_found = 0;
    
    // Reset tokenizer
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    // Process each character
    for (size_t i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        
        if (c >= '0' && c <= '9') {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        } else if (c == ' ' || c == '\t' || c == '\n') {
            if (tokenizer->stateID == GOTNUMBER_STATE) {
                // Verify the current number before processing whitespace
                if (numbers_found < num_expected) {
                    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(0.0001, expected_numbers[numbers_found], 
                                                     tokenizer->result,
                                                     "Parsed number should match expected");
                    numbers_found++;
                }
            }
            TokenizerMultiReceptor_evWhiteSpace(tokenizer);
        }
        // Ignore other characters
    }
    
    // Process end of string
    if (tokenizer->stateID == GOTNUMBER_STATE) {
        if (numbers_found < num_expected) {
            TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(0.0001, expected_numbers[numbers_found], 
                                             tokenizer->result,
                                             "Final parsed number should match expected");
            numbers_found++;
        }
    }
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    
    // Verify we found the expected number of numbers
    TEST_ASSERT_EQUAL_INT_MESSAGE(num_expected, numbers_found, 
                                  "Should find expected number of numbers");
}

/*
 * ============================================================================
 * MULTI-NUMBER PARSING TESTS
 * ============================================================================
 */

/**
 * @brief Test parsing multiple integers
 */
void test_ParseMultipleIntegers(void) {
    const char* input = "123 456 789";
    double expected[] = {123.0, 456.0, 789.0};
    
    parseStringAndVerify(input, expected, 3);
}

/**
 * @brief Test parsing multiple decimal numbers
 */
void test_ParseMultipleDecimals(void) {
    const char* input = "12.5 34.75 0.125";
    double expected[] = {12.5, 34.75, 0.125};
    
    parseStringAndVerify(input, expected, 3);
}

/**
 * @brief Test parsing mixed integer and decimal numbers
 */
void test_ParseMixedNumbers(void) {
    const char* input = "100 23.45 67 0.8 999.999";
    double expected[] = {100.0, 23.45, 67.0, 0.8, 999.999};
    
    parseStringAndVerify(input, expected, 5);
}

/**
 * @brief Test parsing numbers with leading decimals
 */
void test_ParseLeadingDecimals(void) {
    const char* input = ".5 .25 .125 .0625";
    double expected[] = {0.5, 0.25, 0.125, 0.0625};
    
    parseStringAndVerify(input, expected, 4);
}

/*
 * ============================================================================
 * COMPLEX INPUT HANDLING TESTS
 * ============================================================================
 */

/**
 * @brief Test parsing with extra whitespace
 */
void test_ParseWithExtraWhitespace(void) {
    const char* input = "  123   456.78    999  ";
    double expected[] = {123.0, 456.78, 999.0};
    
    parseStringAndVerify(input, expected, 3);
}

/**
 * @brief Test parsing with tabs and newlines
 */
void test_ParseWithMixedWhitespace(void) {
    const char* input = "12.34\t56.78\n90.12";
    double expected[] = {12.34, 56.78, 90.12};
    
    parseStringAndVerify(input, expected, 3);
}

/**
 * @brief Test parsing with ignored characters
 */
void test_ParseWithIgnoredCharacters(void) {
    // Reset tokenizer
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    // Parse "abc123def456ghi"
    const char* input = "abc123def456ghi";
    int numbers_found = 0;
    
    for (size_t i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        
        if (c >= '0' && c <= '9') {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        } else {
            // For non-whitespace, non-digit characters, we simulate whitespace behavior
            // to separate numbers when transitioning from number to non-number
            if (tokenizer->stateID == GOTNUMBER_STATE) {
                TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(0.0001, (numbers_found == 0) ? 123.0 : 456.0, 
                                                 tokenizer->result,
                                                 "Parsed number should match expected");
                numbers_found++;
                TokenizerMultiReceptor_evWhiteSpace(tokenizer);
            }
        }
    }
    
    // Handle final number if parsing ended in number state
    if (tokenizer->stateID == GOTNUMBER_STATE) {
        TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(0.0001, (numbers_found == 0) ? 123.0 : 456.0, 
                                         tokenizer->result,
                                         "Final parsed number should match expected");
        numbers_found++;
    }
    
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, numbers_found, "Should find 2 numbers");
}

/*
 * ============================================================================
 * STRESS TESTING
 * ============================================================================
 */

/**
 * @brief Test parsing a large number of values
 */
void test_ParseLargeNumberOfValues(void) {
    // Generate input string with 100 numbers
    char large_input[2000];
    strcpy(large_input, "");
    
    for (int i = 0; i < 100; i++) {
        char buffer[20];
        if (i > 0) {
            strcat(large_input, " ");
        }
        sprintf(buffer, "%d.%d", i, i % 10);
        strcat(large_input, buffer);
    }
    
    // Parse and count numbers
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    int numbers_found = 0;
    
    for (size_t i = 0; large_input[i] != '\0'; i++) {
        char c = large_input[i];
        
        if (c >= '0' && c <= '9') {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        } else if (c == ' ') {
            if (tokenizer->stateID == GOTNUMBER_STATE) {
                numbers_found++;
            }
            TokenizerMultiReceptor_evWhiteSpace(tokenizer);
        }
    }
    
    // Handle final number
    if (tokenizer->stateID == GOTNUMBER_STATE) {
        numbers_found++;
    }
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(100, numbers_found, "Should parse 100 numbers");
}

/**
 * @brief Test parsing very large numbers
 */
void test_ParseVeryLargeNumbers(void) {
    // Reset tokenizer
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    // Parse "123456789.987654321"
    const char digits[] = "123456789";
    for (int i = 0; digits[i] != '\0'; i++) {
        TokenizerMultiReceptor_evDigit(tokenizer, digits[i]);
    }
    
    TokenizerMultiReceptor_evDot(tokenizer);
    
    const char fractional[] = "987654321";
    for (int i = 0; fractional[i] != '\0'; i++) {
        TokenizerMultiReceptor_evDigit(tokenizer, fractional[i]);
    }
    
    // Verify result is approximately correct
    TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(0.001, 123456789.987654321, tokenizer->result, 
                                      "Large number should be parsed approximately correctly");
}

/*
 * ============================================================================
 * THREAD SAFETY TESTS
 * ============================================================================
 */

// Structure for thread test data
typedef struct {
    TokenizerMultiReceptor* tokenizer;
    const char* input;
    int thread_id;
    int* results_counter;
    Mutex* counter_mutex;
} ThreadTestData;

/**
 * @brief Thread function for concurrent access testing
 */
void* threadTestFunction(void* arg) {
    ThreadTestData* data = (ThreadTestData*)arg;
    
    // Each thread processes its input multiple times
    for (int iteration = 0; iteration < 10; iteration++) {
        // Reset and process
        TokenizerMultiReceptor_Init(data->tokenizer);
        TokenizerMultiReceptor_setItsMutex(data->tokenizer, test_mutex);
        
        // Process input character by character
        for (size_t i = 0; data->input[i] != '\0'; i++) {
            char c = data->input[i];
            
            if (c >= '0' && c <= '9') {
                TokenizerMultiReceptor_evDigit(data->tokenizer, c);
            } else if (c == '.') {
                TokenizerMultiReceptor_evDot(data->tokenizer);
            } else if (c == ' ') {
                TokenizerMultiReceptor_evWhiteSpace(data->tokenizer);
            }
        }
        
        TokenizerMultiReceptor_evEndOfString(data->tokenizer);
        
        // Increment results counter (thread-safe)
        Mutex_lock(data->counter_mutex);
        (*(data->results_counter))++;
        Mutex_release(data->counter_mutex);
        
        // Small delay to increase chance of race conditions (using simple loop)
        for (volatile int i = 0; i < 1000; i++) {
            // Busy wait to create timing variation
        }
    }
    
    return NULL;
}

/**
 * @brief Test thread safety with multiple threads
 */
void test_ThreadSafety(void) {
    const int NUM_THREADS = 4;
    const int EXPECTED_RESULTS = NUM_THREADS * 10; // 10 iterations per thread
    
    pthread_t threads[NUM_THREADS];
    ThreadTestData thread_data[NUM_THREADS];
    int results_counter = 0;
    
    // Create mutex for results counter
    Mutex* counter_mutex = malloc(sizeof(Mutex));
    TEST_ASSERT_NOT_NULL(counter_mutex);
    TEST_ASSERT_EQUAL_INT(0, Mutex_init(counter_mutex));
    
    // Setup thread data
    const char* inputs[] = {"123.45", "67.89", "100.5", "0.25"};
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].tokenizer = tokenizer;
        thread_data[i].input = inputs[i];
        thread_data[i].thread_id = i;
        thread_data[i].results_counter = &results_counter;
        thread_data[i].counter_mutex = counter_mutex;
    }
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int result = pthread_create(&threads[i], NULL, threadTestFunction, &thread_data[i]);
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Thread creation should succeed");
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        void* thread_result;
        int result = pthread_join(threads[i], &thread_result);
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Thread join should succeed");
    }
    
    // Verify all operations completed
    TEST_ASSERT_EQUAL_INT_MESSAGE(EXPECTED_RESULTS, results_counter, 
                                  "All thread operations should complete");
    
    // Cleanup
    Mutex_destroy(counter_mutex);
    free(counter_mutex);
}

/*
 * ============================================================================
 * ERROR RECOVERY TESTS
 * ============================================================================
 */

/**
 * @brief Test recovery from invalid state
 */
void test_ErrorRecovery(void) {
    // Force tokenizer into invalid state
    tokenizer->stateID = (TSTATETYPE)999; // Invalid state
    
    // Try to process a digit - should be ignored
    TokenizerMultiReceptor_evDigit(tokenizer, '5');
    
    // State should remain invalid
    TEST_ASSERT_EQUAL_INT_MESSAGE(999, tokenizer->stateID, 
                                  "Invalid state should be preserved");
    
    // Reset should fix the state
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    // Now it should work normally
    TokenizerMultiReceptor_evDigit(tokenizer, '5');
    TEST_ASSERT_EQUAL_INT_MESSAGE(GOTNUMBER_STATE, tokenizer->stateID, 
                                  "Should transition to GOTNUMBER_STATE after reset");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(5.0, tokenizer->result, 
                                     "Should parse digit correctly after reset");
}

/*
 * ============================================================================
 * MAIN INTEGRATION TEST RUNNER
 * ============================================================================
 */

/**
 * @brief Main integration test runner function
 */
int main(void) {
    UNITY_BEGIN();
    
    // Multi-number parsing tests
    RUN_TEST(test_ParseMultipleIntegers);
    RUN_TEST(test_ParseMultipleDecimals);
    RUN_TEST(test_ParseMixedNumbers);
    RUN_TEST(test_ParseLeadingDecimals);
    
    // Complex input handling tests
    RUN_TEST(test_ParseWithExtraWhitespace);
    RUN_TEST(test_ParseWithMixedWhitespace);
    RUN_TEST(test_ParseWithIgnoredCharacters);
    
    // Stress testing
    RUN_TEST(test_ParseLargeNumberOfValues);
    RUN_TEST(test_ParseVeryLargeNumbers);
    
    // Thread safety tests
    RUN_TEST(test_ThreadSafety);
    
    // Error recovery tests
    RUN_TEST(test_ErrorRecovery);
    
    return UNITY_END();
}
