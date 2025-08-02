
#include "Mutex.h"

// Initialize the mutex
int Mutex_init(Mutex* mutex) {
    if (mutex == NULL) {
        return -1; // Invalid parameter
    }

    int result = pthread_mutex_init(&mutex->mutex, NULL);
    if (result == 0) {
        mutex->initialized = 1;
        return 0; // Success
    }

    mutex->initialized = 0;
    return result; // Error code from pthread_mutex_init
}

// Destroy the mutex
int Mutex_destroy(Mutex* mutex) {
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    int result = pthread_mutex_destroy(&mutex->mutex);
    if (result == 0) {
        mutex->initialized = 0;
    }

    return result;
}

// Lock the mutex (blocks until lock is acquired)
int Mutex_lock(Mutex* mutex) {
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    return pthread_mutex_lock(&mutex->mutex);
}

// Try to lock the mutex without blocking
int Mutex_trylock(Mutex* mutex) {
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    return pthread_mutex_trylock(&mutex->mutex);
}

// Release the mutex
int Mutex_release(Mutex* mutex) {
    if (mutex == NULL || !mutex->initialized) {
        return -1; // Invalid parameter or not initialized
    }

    return pthread_mutex_unlock(&mutex->mutex);
}
