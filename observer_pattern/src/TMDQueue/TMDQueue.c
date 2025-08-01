//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "TMDQueue.h"
#include "NotificationHandle.h"

/**
 * Observer Pattern: Subject Implementation
 * 
 * This file implements the Subject in the Observer pattern.
 * It maintains a list of observers and notifies them of state changes.
 */

static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);

/**
 * Initialize the subject
 */
void TMDQueue_Init(TMDQueue* const me) {
    me->head = 0;
    me->nSubscribers = 0;
    me->size = 0;
    me->itsNotificationHandle = NULL;
    initRelations(me);
}

/**
 * Clean up the subject
 */
void TMDQueue_Cleanup(TMDQueue* const me) {
    cleanUpRelations(me);
}

int TMDQueue_getNextIndex(TMDQueue* const me, int index) {
     /* this operation computes the next index from the
     first using modulo arithmetic
     */
    return (index+1) % QUEUE_SIZE;
}

void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd) {
    /* note that because we never 'remove' data from this
    leaky queue, size only increases to the queue size and
    then stops increasing. Inserion always takes place at the head.
    */
    printf("Inderting at: %d    Data #: %ld", me->head, tmd.timeInterval);
    me->buffer[me->head] = tmd;
    me->head = TMDQueue_getNextIndex(me, me->head);
    if (me->size < QUEUE_SIZE) ++me->size;
    printf("  Storing data value: %d\n", tmd.dataValue);
    TMDQueue_notify(me, tmd);
}

boolean TMDQueue_isEmpty(TMDQueue* const me) {
    return (boolean)(me->size == 0);
}

/**
 * Observer Pattern: NOTIFY method
 * 
 * This is the key method in the Observer pattern that notifies
 * all registered observers about state changes.
 */
void TMDQueue_notify(TMDQueue* const me, const struct TimeMarkedData tmd) {
    struct NotificationHandle *current = me->itsNotificationHandle;

    // Traverse the list of observers and notify each one
    while (current != NULL) {
        // Call the observer's update method
        printf("Notifying observer with data value: %d\n", tmd.dataValue);
        current->updateAddr(current->observerInstance, tmd);
        current = current->itsNotificationHandle;
    }
}

struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index) {
     TimeMarkedData tmd;
     tmd.timeInterval=-1; /* sentinel values */
     tmd.dataValue=-9999;

    if (!TMDQueue_isEmpty(me) &&
        (index>=0) &&
        (index < QUEUE_SIZE)
        && (index < me->size)) {
        tmd = me->buffer[index];
    }
    return tmd;
}

/**
 * Observer Pattern: SUBSCRIBE method
 * 
 * This method registers an observer to receive notifications
 * when the subject's state changes.
 */
void TMDQueue_subscribe(TMDQueue* const me, void* observerInstance, const UpdateFuncPtr updateFuncAddr) {
    struct NotificationHandle *pNH = me->itsNotificationHandle;

    if (pNH == NULL) {
        // Empty list - create first observer node
        me->itsNotificationHandle = NotificationHandle_Create();
        pNH = me->itsNotificationHandle;
    } else {
        // Find end of observer list
        while (pNH->itsNotificationHandle != NULL) {
            pNH = pNH->itsNotificationHandle;
        }

        // Add new observer at the end
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }

    // Store the update function, observer instance, and increment subscriber count
    pNH->updateAddr = updateFuncAddr;
    pNH->observerInstance = observerInstance;
    ++me->nSubscribers;
    printf("Added new observer - total subscribers: %d\n", me->nSubscribers);
}

/**
 * Observer Pattern: UNSUBSCRIBE method
 * 
 * This method removes an observer from the notification list
 * so it no longer receives updates when the subject changes.
 */
int TMDQueue_unsubscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr) {
    
    if (!me || !updateFuncAddr) {
        return 0;
    }

    struct NotificationHandle *current = me->itsNotificationHandle;
    struct NotificationHandle *previous = NULL;

    // If no observers, return 0
    if (current == NULL) {
        return 0;
    }

    // If first observer matches, remove it
    if (current->updateAddr == updateFuncAddr) {
        me->itsNotificationHandle = current->itsNotificationHandle;
        NotificationHandle_Destroy(current);
        --me->nSubscribers;
        printf("Removed observer (first in list) - remaining subscribers: %d\n", me->nSubscribers);
        return 1;
    }

    // Search for the observer in the list
    while (current != NULL) {
        if (current->updateAddr == updateFuncAddr) {
            // Found the observer - remove it
            previous->itsNotificationHandle = current->itsNotificationHandle;
            NotificationHandle_Destroy(current);
            --me->nSubscribers;
            printf("Removed observer - remaining subscribers: %d\n", me->nSubscribers);
            return 1;
        }

        // Move to next observer
        previous = current;
        current = current->itsNotificationHandle;
    }

    // If the target element was not found in the list, return 0
    printf(">>>>>> Didn't remove any subscribers\n");
    return 0;
}

int TMDQueue_getBuffer(const TMDQueue* const me) {
    int iter = 0;
    return iter;
}

struct NotificationHandle* TMDQueue_getItsNotificationHandle(const TMDQueue* const me) {
    return (struct NotificationHandle*)me->itsNotificationHandle;
}

void TMDQueue_setItsNotificationHandle(TMDQueue* const me, struct NotificationHandle* p_NotificationHandle) {
    me->itsNotificationHandle = p_NotificationHandle;
}

TMDQueue * TMDQueue_Create(void) {
    TMDQueue* me = (TMDQueue *) malloc(sizeof(TMDQueue));
    if(me!=NULL)
    {
        TMDQueue_Init(me);
    }
    return me;
}

void TMDQueue_Destroy(TMDQueue* const me) {
    if(me!=NULL)
    {
        TMDQueue_Cleanup(me);
    }
    free(me);
}

static void initRelations(TMDQueue* const me) {
    {
        int iter = 0;
        while (iter < QUEUE_SIZE){
            TimeMarkedData_Init(&((me->buffer)[iter]));
            TimeMarkedData_setItsTMDQueue(&((me->buffer)[iter]), me);
            iter++;
        }
    }
}

static void cleanUpRelations(TMDQueue* const me) {
    {
        int iter = 0;
        while (iter < QUEUE_SIZE){
            TimeMarkedData_Cleanup(&((me->buffer)[iter]));
            iter++;
        }
    }
    if(me->itsNotificationHandle != NULL)
    {
        me->itsNotificationHandle = NULL;
    }
}
