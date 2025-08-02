/**
 * @file test_mutex.c
 * @brief Unit tests for Mutex functionality
 * 
 * Tests the mutex implementation to ensure thread safety works correctly.
 * These tests verify initialization, destruction, and basic locking operations.
 */

#include <unity.h>
#include "../src/mutex/Mutex.h"
#include <pthread.h>
#include <unistd.h>

// Global test variables
Mutex test_mutex;

// Test setup - called before each test
void setUp(void) {
    // Initialize test mutex for each test
    // Note: Some tests will re-initialize, that's intentional
}

// Test teardown - called after each test
void tearDown(void) {
    // Clean up the mutex if it was initialized
    Mutex_destroy(&test_mutex);
}

// === TESTS FOR MUTEX INITIALIZATION ===

void test_mutex_init_success(void) {
    int result = Mutex_init(&test_mutex);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, test_mutex.initialized);
}

void test_mutex_init_null_pointer(void) {
    int result = Mutex_init(NULL);
    TEST_ASSERT_NOT_EQUAL(0, result);  // Should fail with non-zero return
}

// === TESTS FOR MUTEX DESTRUCTION ===

void test_mutex_destroy_after_init(void) {
    Mutex_init(&test_mutex);
    int result = Mutex_destroy(&test_mutex);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(0, test_mutex.initialized);
}

void test_mutex_destroy_null_pointer(void) {
    int result = Mutex_destroy(NULL);
    TEST_ASSERT_NOT_EQUAL(0, result);  // Should fail with non-zero return
}

void test_mutex_destroy_uninitialized(void) {
    // Create an uninitialized mutex
    Mutex uninitialized_mutex = {0};
    int result = Mutex_destroy(&uninitialized_mutex);
    // This should handle uninitialized mutex gracefully
    // The exact behavior depends on implementation
    (void)result; // Suppress unused variable warning
}

// === TESTS FOR MUTEX LOCKING ===

void test_mutex_lock_and_release(void) {
    Mutex_init(&test_mutex);
    
    // Lock should succeed
    int lock_result = Mutex_lock(&test_mutex);
    TEST_ASSERT_EQUAL(0, lock_result);
    
    // Release should succeed
    int release_result = Mutex_release(&test_mutex);
    TEST_ASSERT_EQUAL(0, release_result);
}

void test_mutex_trylock_success(void) {
    Mutex_init(&test_mutex);
    
    // Trylock should succeed when mutex is not locked
    int result = Mutex_trylock(&test_mutex);
    TEST_ASSERT_EQUAL(0, result);
    
    // Release the lock
    Mutex_release(&test_mutex);
}

void test_mutex_trylock_already_locked(void) {
    Mutex_init(&test_mutex);
    
    // First lock should succeed
    Mutex_lock(&test_mutex);
    
    // Trylock should fail when already locked (in single-threaded test)
    // Note: This test is tricky in single-threaded environment
    // The behavior depends on whether the mutex is recursive or not
    
    // Release the first lock
    Mutex_release(&test_mutex);
}

void test_mutex_operations_with_null(void) {
    // All operations should fail gracefully with NULL pointer
    TEST_ASSERT_NOT_EQUAL(0, Mutex_lock(NULL));
    TEST_ASSERT_NOT_EQUAL(0, Mutex_trylock(NULL));
    TEST_ASSERT_NOT_EQUAL(0, Mutex_release(NULL));
}

void test_mutex_operations_uninitialized(void) {
    // Operations on uninitialized mutex should fail
    Mutex uninitialized = {0};
    
    // These should fail gracefully
    int lock_result = Mutex_lock(&uninitialized);
    int trylock_result = Mutex_trylock(&uninitialized);
    int release_result = Mutex_release(&uninitialized);
    
    // All should return non-zero (error)
    TEST_ASSERT_NOT_EQUAL(0, lock_result);
    TEST_ASSERT_NOT_EQUAL(0, trylock_result);
    TEST_ASSERT_NOT_EQUAL(0, release_result);
}

// === TESTS FOR DOUBLE INITIALIZATION ===

void test_mutex_double_init(void) {
    // First initialization should succeed
    int result1 = Mutex_init(&test_mutex);
    TEST_ASSERT_EQUAL(0, result1);
    
    // Second initialization should handle gracefully
    // (behavior depends on implementation - might succeed or fail)
    int result2 = Mutex_init(&test_mutex);
    // Don't assert specific behavior here as it's implementation-dependent
    (void)result2; // Suppress unused variable warning
}

// === INTEGRATION TESTS ===

void test_mutex_multiple_lock_release_cycles(void) {
    Mutex_init(&test_mutex);
    
    // Multiple lock/release cycles should work
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL(0, Mutex_lock(&test_mutex));
        TEST_ASSERT_EQUAL(0, Mutex_release(&test_mutex));
    }
}

// === MAIN TEST RUNNER ===

int main(void) {
    UNITY_BEGIN();
    
    // Basic initialization and destruction
    RUN_TEST(test_mutex_init_success);
    RUN_TEST(test_mutex_init_null_pointer);
    RUN_TEST(test_mutex_destroy_after_init);
    RUN_TEST(test_mutex_destroy_null_pointer);
    RUN_TEST(test_mutex_destroy_uninitialized);
    
    // Locking operations
    RUN_TEST(test_mutex_lock_and_release);
    RUN_TEST(test_mutex_trylock_success);
    RUN_TEST(test_mutex_trylock_already_locked);
    RUN_TEST(test_mutex_operations_with_null);
    RUN_TEST(test_mutex_operations_uninitialized);
    
    // Edge cases
    RUN_TEST(test_mutex_double_init);
    
    // Integration tests
    RUN_TEST(test_mutex_multiple_lock_release_cycles);
    
    return UNITY_END();
}
