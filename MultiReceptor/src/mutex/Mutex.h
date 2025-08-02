
//
// Mutex Header File
// 
// This header defines a thread synchronization primitive using POSIX threads (pthreads).
// The Mutex structure provides a wrapper around pthread_mutex_t with additional
// state tracking for safer operation.
//
// Thread Safety: This mutex implementation is thread-safe when used correctly
// POSIX Compliance: Uses standard POSIX pthread mutex functions
//

#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

/*
 * ============================================================================
 * MUTEX STRUCTURE DEFINITION
 * ============================================================================
 */

/**
 * @brief Mutex structure for mutual exclusion using POSIX threads
 * 
 * This structure wraps a POSIX pthread mutex with additional state tracking
 * to provide safer mutex operations and better error handling.
 * 
 * Members:
 * - mutex: The underlying POSIX mutex primitive
 * - initialized: Flag to track whether the mutex has been properly initialized
 */
typedef struct Mutex {
    pthread_mutex_t mutex;  // POSIX mutex primitive
    int initialized;        // Initialization state flag (1 = initialized, 0 = not initialized)
} Mutex;

/*
 * ============================================================================
 * MUTEX OPERATION FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Initialize the mutex for use
 * @param mutex Pointer to the Mutex structure to initialize
 * @return 0 on success, negative value on invalid parameter, 
 *         positive value on pthread error
 * 
 * This function must be called before any other mutex operations.
 * It initializes the underlying pthread mutex with default attributes.
 */
int Mutex_init(Mutex* mutex);

/**
 * @brief Destroy the mutex and clean up resources
 * @param mutex Pointer to the Mutex structure to destroy
 * @return 0 on success, negative value on invalid parameter or not initialized,
 *         positive value on pthread error
 * 
 * This function should be called when the mutex is no longer needed.
 * After calling this function, the mutex should not be used unless
 * reinitialized with Mutex_init().
 */
int Mutex_destroy(Mutex* mutex);

/**
 * @brief Lock the mutex (blocks until lock is acquired)
 * @param mutex Pointer to the Mutex structure to lock
 * @return 0 on success, negative value on invalid parameter or not initialized,
 *         positive value on pthread error
 * 
 * This function will block the calling thread until the mutex becomes
 * available. Only one thread can hold the lock at a time.
 */
int Mutex_lock(Mutex* mutex);

/**
 * @brief Try to lock the mutex without blocking
 * @param mutex Pointer to the Mutex structure to try to lock
 * @return 0 on success (lock acquired), negative value on invalid parameter 
 *         or not initialized, EBUSY if already locked, other positive values 
 *         on pthread error
 * 
 * This function attempts to acquire the lock immediately. If the mutex
 * is already locked by another thread, it returns immediately with EBUSY
 * rather than blocking.
 */
int Mutex_trylock(Mutex* mutex);

/**
 * @brief Release the mutex lock
 * @param mutex Pointer to the Mutex structure to unlock
 * @return 0 on success, negative value on invalid parameter or not initialized,
 *         positive value on pthread error
 * 
 * This function releases a previously acquired mutex lock, allowing other
 * threads to acquire the lock. Should only be called by the thread that
 * currently holds the lock.
 */
int Mutex_release(Mutex* mutex);

#endif // MUTEX_H
