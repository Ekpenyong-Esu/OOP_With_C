
#ifndef TSREventQueue_H
#define TSREventQueue_H

#include "../TokenizeAsyncSinglePkg/TokenizeAsyncSinglePkg.h"

struct Mutex;

// Event queue structure for thread-safe event management
typedef struct TSREventQueue TSREventQueue;
struct TSREventQueue {
    Event queue[QSIZE];    // Array of events
    int size;              // Current number of events in the queue
    int head;              // Index for next event insertion
    int tail;              // Index for next event removal
    struct Mutex* mutexPtr;// Pointer to mutex for thread safety
};

// Initialize the event queue
void TSREventQueue_Init(TSREventQueue* const eventQueue);

// Cleanup the event queue
void TSREventQueue_Cleanup(TSREventQueue* const queue);

// Check if the event queue is empty
int TSREventQueue_isEmpty(TSREventQueue* const eventQueue);

// Check if the event queue is full
int TSREventQueue_isFull(TSREventQueue* const eventQueue);

// Post an event to the queue
int TSREventQueue_post(TSREventQueue* const eventQueue, Event event);

// Pull the oldest event from the queue
Event TSREventQueue_pull(TSREventQueue* const eventQueue);

// Get the mutex associated with the event queue
struct Mutex* TSREventQueue_getItsMutex(const TSREventQueue* const eventQueue);

// Set the mutex for the event queue
void TSREventQueue_setItsMutex(TSREventQueue* const queue, struct Mutex* mutexPtr);

// Create a new event queue instance
TSREventQueue * TSREventQueue_Create(void);

// Destroy an event queue instance
void TSREventQueue_Destroy(TSREventQueue* const eventQueue);

#endif
