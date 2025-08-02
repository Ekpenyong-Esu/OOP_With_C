
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

// Mutex structure for mutual exclusion using POSIX threads
typedef struct Mutex {
    pthread_mutex_t mutex;  // POSIX mutex
    int initialized;        // Flag to track initialization
} Mutex;

// Initialize the mutex
int Mutex_init(Mutex* mutex);

// Destroy the mutex
int Mutex_destroy(Mutex* mutex);

// Lock the mutex (blocks until lock is acquired)
int Mutex_lock(Mutex* mutex);

// Try to lock the mutex without blocking
int Mutex_trylock(Mutex* mutex);

// Release the mutex
int Mutex_release(Mutex* mutex);

#endif // MUTEX_H
