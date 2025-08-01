
#ifndef MUTEX_H
#define MUTEX_H

// Mutex structure for mutual exclusion (stub for single-threaded use)
typedef struct Mutex {
    int dummy; // Placeholder field
} Mutex;

// Lock the mutex (no-op in this implementation)
void Mutex_lock(Mutex* mutex);

// Release the mutex (no-op in this implementation)
void Mutex_release(Mutex* mutex);

#endif // MUTEX_H
