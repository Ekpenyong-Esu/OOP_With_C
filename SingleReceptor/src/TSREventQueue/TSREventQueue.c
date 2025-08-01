
#include <stddef.h>
#include <stdlib.h>
#include "TSREventQueue.h"
#include "../mutex/Mutex.h"
#include "../TokenizeAsyncSinglePkg/TokenizeAsyncSinglePkg.h"

// Internal helper to clean up relations (mutex pointer)
static void cleanUpRelations(TSREventQueue* const eventQueue);

// Initialize the event queue
void TSREventQueue_Init(TSREventQueue* const eventQueue) {
    if (eventQueue == NULL) {
        return; // Fail gracefully if queue is null
    }
    eventQueue->head = 0;
    eventQueue->size = 0;
    eventQueue->tail = 0;
    eventQueue->mutexPtr = NULL;
}

// Cleanup the event queue
void TSREventQueue_Cleanup(TSREventQueue* const eventQueue) {
    cleanUpRelations(eventQueue);
}

// Check if the event queue is empty
int TSREventQueue_isEmpty(TSREventQueue* const eventQueue) {
    if (eventQueue == NULL) {
        return 1; // Consider null queue as empty
    }
    return eventQueue->size <= 0;
}

// Check if the event queue is full
int TSREventQueue_isFull(TSREventQueue* const eventQueue) {
    if (eventQueue == NULL) {
        return 1; // Consider null queue as full to prevent writes
    }
    return eventQueue->size >= QSIZE-1;
}

// Post an event to the queue and signal its presence
int TSREventQueue_post(TSREventQueue* const eventQueue, Event event) {
    if (eventQueue == NULL) {
        return 0; // Fail if queue is null
    }

    Mutex_lock(eventQueue->mutexPtr);
    if (!TSREventQueue_isFull(eventQueue)) {
        eventQueue->queue[eventQueue->head] = event;
        eventQueue->head = (eventQueue->head + 1) % QSIZE;
        eventQueue->size += 1;
        Mutex_release(eventQueue->mutexPtr);
        postSignal(); // Signal that an event is present
        return 1;
    }
    Mutex_release(eventQueue->mutexPtr);
    return 0;
}

// Pull the oldest event from the queue
// Should only be called when there is an event waiting
Event TSREventQueue_pull(TSREventQueue* const eventQueue) {
    Event event = {0}; // Initialize to prevent garbage data
    if (eventQueue == NULL) {
        return event; // Return empty event if queue is null
    }

    Mutex_lock(eventQueue->mutexPtr);
    if (!TSREventQueue_isEmpty(eventQueue)) {
        event = eventQueue->queue[eventQueue->tail];
        eventQueue->tail = (eventQueue->tail + 1) % QSIZE;
        eventQueue->size -= 1;
    }
    Mutex_release(eventQueue->mutexPtr);
    return event;
}

// Get the mutex associated with the event queue
struct Mutex* TSREventQueue_getItsMutex(const TSREventQueue* const eventQueue) {
    return (struct Mutex*)eventQueue->mutexPtr;
}

// Set the mutex for the event queue
void TSREventQueue_setItsMutex(TSREventQueue* const eventQueue, struct Mutex* mutexPtr) {
    eventQueue->mutexPtr = mutexPtr;
}

// Create a new event queue instance
TSREventQueue * TSREventQueue_Create(void) {
    TSREventQueue* eventQueue = (TSREventQueue *) malloc(sizeof(TSREventQueue));
    if(eventQueue != NULL) {
        TSREventQueue_Init(eventQueue);
    }
    return eventQueue;
}

// Destroy an event queue instance
void TSREventQueue_Destroy(TSREventQueue* const eventQueue) {
    if(eventQueue != NULL) {
        TSREventQueue_Cleanup(eventQueue);
    }
    free(eventQueue);
}

// Internal helper to clean up relations (mutex pointer)
static void cleanUpRelations(TSREventQueue* const eventQueue) {
    if(eventQueue->mutexPtr != NULL) {
        eventQueue->mutexPtr = NULL;
    }
}
