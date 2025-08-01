//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TMDQUEUE_H
#define CLIENT_SERVER_PATTERN_TMDQUEUE_H

#include "ECGPkg.h"
#include "TimeMarkedData.h"
#include "NotificationHandle.h" // Include NotificationHandle.h which has the UpdateFuncPtr definition

typedef struct TMDQueue TMDQueue;

/**
 * Observer Pattern: SUBJECT class
 * 
 * TMDQueue acts as the Subject in the Observer pattern.
 * It maintains a list of observers (NotificationHandles) and notifies 
 * them when new data is added to the queue.
 */
struct TMDQueue {
    int head;                                   // Current position in circular buffer
    int nSubscribers;                           // Number of observers
    int size;                                   // Current size of data in the buffer
    struct TimeMarkedData buffer[QUEUE_SIZE];   // Circular buffer of data
    struct NotificationHandle* itsNotificationHandle; // Linked list of observers
};

/* Constructors and destructors:*/
void TMDQueue_Init(TMDQueue* const me);
void TMDQueue_Cleanup(TMDQueue* const me);

/* Queue operations */
int TMDQueue_getNextIndex(TMDQueue* const me, int index);
void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd);
boolean TMDQueue_isEmpty(TMDQueue* const me);
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index);

/**
 * Observer Pattern: Core Subject Methods
 * 
 * These methods implement the key Subject functionality:
 * - notify: Inform all observers of state changes
 * - subscribe: Register an observer to receive notifications
 * - unsubscribe: Remove an observer from notification list
 */
void TMDQueue_notify(TMDQueue* const me, const struct TimeMarkedData tmd);
void TMDQueue_subscribe(TMDQueue* const me, void* observerInstance, const UpdateFuncPtr updateFuncAddr);
int TMDQueue_unsubscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr);

/* Accessor methods */
int TMDQueue_getBuffer(const TMDQueue* const me);
struct NotificationHandle* TMDQueue_getItsNotificationHandle(const TMDQueue* const me);
void TMDQueue_setItsNotificationHandle(TMDQueue* const me, struct NotificationHandle* p_NotificationHandle);

/* Creation and destruction */
TMDQueue* TMDQueue_Create(void);
void TMDQueue_Destroy(TMDQueue* const me);


#endif //CLIENT_SERVER_PATTERN_TMDQUEUE_H
