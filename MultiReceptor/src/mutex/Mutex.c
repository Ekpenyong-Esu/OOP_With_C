
//
// Mutex Implementation
//
// This file implements thread synchronization primitives using POSIX threads.
// The implementation provides a safe wrapper around pthread_mutex_t with
// proper error handling and state tracking.
//
// Error Handling Strategy:
// - Return -1 for invalid parameters or uninitialized mutexes
// - Return 0 for successful operations
// - Return positive values for pthread-specific errors
//

#include "Mutex.h"

/*
 * ============================================================================
 * MUTEX LIFECYCLE FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Initialize the mutex for use
 * @param mutex Pointer to the Mutex structure to initialize
 * @return 0 on success, -1 on invalid parameter, pthread error code on failure
 * 
 * This function initializes the pthread mutex with default attributes and
 * sets the initialized flag. Must be called before any other operations.
 */
int Mutex_init(Mutex* mutex) {
    // Validate input parameter
    if (mutex == NULL) {
        return -1; // Invalid parameter
    }

    // Initialize the pthread mutex with default attributes
    int result = pthread_mutex_init(&mutex->mutex, NULL);
    if (result == 0) {
        // Success: mark as initialized
        mutex->initialized = 1;
        return 0;
    }

    // Failure: ensure not marked as initialized
    mutex->initialized = 0;
    return result; // Return pthread error code
}

/**
 * @brief Destroy the mutex and clean up resources
 * @param mutex Pointer to the Mutex structure to destroy
 * @return 0 on success, -1 on invalid parameter or not initialized, 
 *         pthread error code on failure
 * 
 * This function destroys the pthread mutex and marks it as uninitialized.
 * The mutex should not be used after calling this function unless
 * reinitialized.
 */
int Mutex_destroy(Mutex* mutex) {
    // Validate input parameter and initialization state
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    // Destroy the pthread mutex
    int result = pthread_mutex_destroy(&mutex->mutex);
    if (result == 0) {
        // Success: mark as uninitialized
        mutex->initialized = 0;
    }

    return result; // Return 0 on success, pthread error code on failure
}

/*
 * ============================================================================
 * MUTEX LOCKING FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Lock the mutex (blocks until lock is acquired)
 * @param mutex Pointer to the Mutex structure to lock
 * @return 0 on success, -1 on invalid parameter or not initialized,
 *         pthread error code on failure
 * 
 * This function will block the calling thread until the mutex becomes
 * available. Use this for exclusive access to shared resources.
 */
int Mutex_lock(Mutex* mutex) {
    // Validate input parameter and initialization state
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    // Attempt to acquire the lock (blocking call)
    return pthread_mutex_lock(&mutex->mutex);
}

/**
 * @brief Try to lock the mutex without blocking
 * @param mutex Pointer to the Mutex structure to try to lock
 * @return 0 on success (lock acquired), -1 on invalid parameter or not initialized,
 *         EBUSY if already locked, other pthread error codes on failure
 * 
 * This function attempts to acquire the lock immediately. If the mutex
 * is already locked, it returns EBUSY rather than blocking the thread.
 */
int Mutex_trylock(Mutex* mutex) {
    // Validate input parameter and initialization state
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    // Attempt to acquire the lock without blocking
    return pthread_mutex_trylock(&mutex->mutex);
}

/**
 * @brief Release the mutex lock
 * @param mutex Pointer to the Mutex structure to unlock
 * @return 0 on success, -1 on invalid parameter or not initialized,
 *         pthread error code on failure
 * 
 * This function releases a previously acquired mutex lock. Should only
 * be called by the thread that currently holds the lock.
 */
int Mutex_release(Mutex* mutex) {
    // Validate input parameter and initialization state
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    // Release the mutex lock
    return pthread_mutex_unlock(&mutex->mutex);
}
