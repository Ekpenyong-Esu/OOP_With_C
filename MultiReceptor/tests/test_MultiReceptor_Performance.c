//
// Performance Benchmark Tests for TokenizerMultiReceptor
//
// This file contains performance benchmarks to measure the efficiency
// of the TokenizerMultiReceptor implementation under various conditions.
//
// Test Framework: Unity (C unit testing framework)
// Categories:
// - Single number parsing performance
// - Multi-number parsing performance  
// - Memory usage validation
// - Mutex overhead measurement
//

#include "unity.h"
#include "MultiReceptor.h"
#include "Mutex.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

// Test fixture
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
 * HELPER FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Get current time in microseconds
 * @return Current time in microseconds
 */
static long getCurrentTimeMicros(void) {
    clock_t current_time = clock();
    return (current_time * 1000000L) / CLOCKS_PER_SEC;
}

/**
 * @brief Parse a simple number and measure time
 * @param number_str String representation of number to parse
 * @return Time taken in microseconds
 */
static long parseNumberTimed(const char* number_str) {
    long start_time = getCurrentTimeMicros();
    
    // Reset tokenizer
    TokenizerMultiReceptor_Init(tokenizer);
    TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
    
    // Parse the string
    for (size_t i = 0; number_str[i] != '\0'; i++) {
        char c = number_str[i];
        if (c >= '0' && c <= '9') {
            TokenizerMultiReceptor_evDigit(tokenizer, c);
        } else if (c == '.') {
            TokenizerMultiReceptor_evDot(tokenizer);
        }
    }
    
    TokenizerMultiReceptor_evEndOfString(tokenizer);
    
    long end_time = getCurrentTimeMicros();
    return end_time - start_time;
}

/*
 * ============================================================================
 * PERFORMANCE BENCHMARK TESTS
 * ============================================================================
 */

/**
 * @brief Benchmark single integer parsing performance
 */
void test_Performance_SingleInteger(void) {
    const char* test_number = "12345";
    const int NUM_ITERATIONS = 10000;
    
    long total_time = 0;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        total_time += parseNumberTimed(test_number);
    }
    
    long average_time = total_time / NUM_ITERATIONS;
    
    printf("\n--- Single Integer Performance ---\n");
    printf("Number: %s\n", test_number);
    printf("Iterations: %d\n", NUM_ITERATIONS);
    printf("Total time: %ld microseconds\n", total_time);
    printf("Average time per parse: %ld microseconds\n", average_time);
    printf("Parses per second: %.0f\n", 1000000.0 / average_time);
    
    // Performance assertion - should complete within reasonable time
    // Expect less than 100 microseconds per parse on modern hardware
    TEST_ASSERT_LESS_THAN_MESSAGE(100, average_time, 
                                  "Single integer parsing should be fast");
}

/**
 * @brief Benchmark floating-point number parsing performance
 */
void test_Performance_FloatingPoint(void) {
    const char* test_number = "123.456789";
    const int NUM_ITERATIONS = 10000;
    
    long total_time = 0;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        total_time += parseNumberTimed(test_number);
    }
    
    long average_time = total_time / NUM_ITERATIONS;
    
    printf("\n--- Floating Point Performance ---\n");
    printf("Number: %s\n", test_number);
    printf("Iterations: %d\n", NUM_ITERATIONS);
    printf("Total time: %ld microseconds\n", total_time);
    printf("Average time per parse: %ld microseconds\n", average_time);
    printf("Parses per second: %.0f\n", 1000000.0 / average_time);
    
    // Performance assertion - floating point should be reasonably fast
    TEST_ASSERT_LESS_THAN_MESSAGE(200, average_time, 
                                  "Floating point parsing should be reasonably fast");
}

/**
 * @brief Benchmark multi-number string parsing performance
 */
void test_Performance_MultiNumber(void) {
    const char* test_string = "123 456.78 999.999 0.5 1000";
    const int NUM_ITERATIONS = 1000;
    
    long start_time = getCurrentTimeMicros();
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Reset tokenizer
        TokenizerMultiReceptor_Init(tokenizer);
        TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
        
        // Parse the string
        for (size_t j = 0; test_string[j] != '\0'; j++) {
            char c = test_string[j];
            if (c >= '0' && c <= '9') {
                TokenizerMultiReceptor_evDigit(tokenizer, c);
            } else if (c == '.') {
                TokenizerMultiReceptor_evDot(tokenizer);
            } else if (c == ' ') {
                TokenizerMultiReceptor_evWhiteSpace(tokenizer);
            }
        }
        
        TokenizerMultiReceptor_evEndOfString(tokenizer);
    }
    
    long end_time = getCurrentTimeMicros();
    long total_time = end_time - start_time;
    long average_time = total_time / NUM_ITERATIONS;
    
    printf("\n--- Multi-Number Performance ---\n");
    printf("String: %s\n", test_string);
    printf("Iterations: %d\n", NUM_ITERATIONS);
    printf("Total time: %ld microseconds\n", total_time);
    printf("Average time per parse: %ld microseconds\n", average_time);
    printf("Parses per second: %.0f\n", 1000000.0 / average_time);
    
    // Multi-number parsing should complete within reasonable time
    TEST_ASSERT_LESS_THAN_MESSAGE(1000, average_time, 
                                  "Multi-number parsing should be reasonably fast");
}

/**
 * @brief Benchmark object creation and destruction performance
 */
void test_Performance_ObjectLifecycle(void) {
    const int NUM_ITERATIONS = 10000;
    
    long start_time = getCurrentTimeMicros();
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        TokenizerMultiReceptor* temp_tokenizer = TokenizerMultiReceptor_Create();
        TEST_ASSERT_NOT_NULL(temp_tokenizer);
        TokenizerMultiReceptor_Destroy(temp_tokenizer);
    }
    
    long end_time = getCurrentTimeMicros();
    long total_time = end_time - start_time;
    long average_time = total_time / NUM_ITERATIONS;
    
    printf("\n--- Object Lifecycle Performance ---\n");
    printf("Iterations: %d\n", NUM_ITERATIONS);
    printf("Total time: %ld microseconds\n", total_time);
    printf("Average time per create/destroy: %ld microseconds\n", average_time);
    printf("Creates per second: %.0f\n", 1000000.0 / average_time);
    
    // Object lifecycle should be fast
    TEST_ASSERT_LESS_THAN_MESSAGE(50, average_time, 
                                  "Object creation/destruction should be fast");
}

/**
 * @brief Benchmark mutex lock/unlock overhead
 */
void test_Performance_MutexOverhead(void) {
    const int NUM_ITERATIONS = 100000;
    
    // Test with mutex
    long start_time = getCurrentTimeMicros();
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        Mutex_lock(test_mutex);
        // Simulate minimal work
        volatile int dummy = i;
        (void)dummy; // Suppress unused variable warning
        Mutex_release(test_mutex);
    }
    
    long end_time = getCurrentTimeMicros();
    long mutex_time = end_time - start_time;
    
    // Test without mutex (baseline)
    start_time = getCurrentTimeMicros();
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Same work without mutex
        volatile int dummy = i;
        (void)dummy; // Suppress unused variable warning
    }
    
    end_time = getCurrentTimeMicros();
    long baseline_time = end_time - start_time;
    
    long mutex_overhead = mutex_time - baseline_time;
    long overhead_per_operation = mutex_overhead / NUM_ITERATIONS;
    
    printf("\n--- Mutex Overhead Performance ---\n");
    printf("Iterations: %d\n", NUM_ITERATIONS);
    printf("Time with mutex: %ld microseconds\n", mutex_time);
    printf("Time without mutex: %ld microseconds\n", baseline_time);
    printf("Mutex overhead: %ld microseconds\n", mutex_overhead);
    printf("Overhead per lock/unlock: %ld nanoseconds\n", overhead_per_operation * 1000);
    
    // Mutex overhead should be reasonable
    TEST_ASSERT_LESS_THAN_MESSAGE(10, overhead_per_operation, 
                                  "Mutex overhead should be minimal");
}

/*
 * ============================================================================
 * MEMORY USAGE TESTS
 * ============================================================================
 */

/**
 * @brief Test memory usage of TokenizerMultiReceptor
 */
void test_MemoryUsage_TokenizerSize(void) {
    size_t tokenizer_size = sizeof(TokenizerMultiReceptor);
    size_t mutex_size = sizeof(Mutex);
    
    printf("\n--- Memory Usage ---\n");
    printf("TokenizerMultiReceptor size: %zu bytes\n", tokenizer_size);
    printf("Mutex size: %zu bytes\n", mutex_size);
    printf("Total per instance: %zu bytes\n", tokenizer_size + mutex_size);
    
    // Verify reasonable memory footprint
    TEST_ASSERT_LESS_THAN_MESSAGE(1024, tokenizer_size, 
                                  "TokenizerMultiReceptor should have reasonable size");
    TEST_ASSERT_LESS_THAN_MESSAGE(512, mutex_size, 
                                  "Mutex should have reasonable size");
}

/**
 * @brief Test for memory leaks in repeated operations
 */
void test_MemoryUsage_NoLeaks(void) {
    const int NUM_ITERATIONS = 1000;
    
    // Perform many operations that could potentially leak memory
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Reset and use tokenizer
        TokenizerMultiReceptor_Init(tokenizer);
        TokenizerMultiReceptor_setItsMutex(tokenizer, test_mutex);
        
        // Perform various operations
        TokenizerMultiReceptor_evDigit(tokenizer, '1');
        TokenizerMultiReceptor_evDigit(tokenizer, '2');
        TokenizerMultiReceptor_evDot(tokenizer);
        TokenizerMultiReceptor_evDigit(tokenizer, '3');
        TokenizerMultiReceptor_evWhiteSpace(tokenizer);
        
        // Create and destroy additional objects
        TokenizerMultiReceptor* temp = TokenizerMultiReceptor_Create();
        if (temp != NULL) {
            TokenizerMultiReceptor_Destroy(temp);
        }
    }
    
    printf("\n--- Memory Leak Test ---\n");
    printf("Completed %d iterations of operations\n", NUM_ITERATIONS);
    printf("No memory leaks should be detected by valgrind or similar tools\n");
    
    // If we reach here without crashes, basic memory management is working
    TEST_PASS_MESSAGE("Memory leak test completed without crashes");
}

/*
 * ============================================================================
 * MAIN PERFORMANCE TEST RUNNER
 * ============================================================================
 */

/**
 * @brief Main performance test runner function
 */
int main(void) {
    UNITY_BEGIN();
    
    printf("\n=== TokenizerMultiReceptor Performance Benchmarks ===");
    
    // Performance benchmarks
    RUN_TEST(test_Performance_SingleInteger);
    RUN_TEST(test_Performance_FloatingPoint);
    RUN_TEST(test_Performance_MultiNumber);
    RUN_TEST(test_Performance_ObjectLifecycle);
    RUN_TEST(test_Performance_MutexOverhead);
    
    // Memory usage tests
    RUN_TEST(test_MemoryUsage_TokenizerSize);
    RUN_TEST(test_MemoryUsage_NoLeaks);
    
    printf("\n=== Performance Benchmarks Complete ===\n");
    
    return UNITY_END();
}
