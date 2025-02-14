//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "TMDQueue.h"
#include "NotificationHandle.h"


static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);

void TMDQueue_Init(TMDQueue* const me) {
    me->head = 0;
    me->nSubscribers = 0;
    me->size = 0;
    me->itsNotificationHandle = NULL;
    initRelations(me);
}

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

void TMDQueue_notify(TMDQueue* const me, const struct TimeMarkedData tmd) {
    struct NotificationHandle *current = me->itsNotificationHandle;

    // Traverse the list of NotificationHandle instances and call the updateAddr function for each one
    while (current != NULL) {
        printf("----->> calling updateAddr on pNH %p\n", current);
        current->updateAddr(NULL, tmd);
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

void TMDQueue_subscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr) {
    struct NotificationHandle *pNH = me->itsNotificationHandle;

    if (pNH == NULL) {
        // Empty list, create a new Notification Handle
        me->itsNotificationHandle = NotificationHandle_Create();
        pNH = me->itsNotificationHandle;
    } else {
        // Search for the end of the list
        while (pNH->itsNotificationHandle != NULL) {
            pNH = pNH->itsNotificationHandle;
        }

        // Add a new Notification Handle at the end of the list
        pNH->itsNotificationHandle = NotificationHandle_Create();
        pNH = pNH->itsNotificationHandle;
    }

    // Set the callback address and increment the subscriber count
    pNH->updateAddr = updateFuncAddr;
    ++me->nSubscribers;
}

int TMDQueue_unsubscribe(TMDQueue* const me, const UpdateFuncPtr updateFuncAddr) {
    
    if (!me || !updateFuncAddr) {
        return 0;
    }

    struct NotificationHandle *current = me->itsNotificationHandle;
    struct NotificationHandle *previous = NULL;

    // If the list is empty, return 0
    if (current == NULL) {
        return 0;
    }

    // If the first element matches the target, update the head of the list and free the old head
    if (current->updateAddr == updateFuncAddr) {
        me->itsNotificationHandle = current->itsNotificationHandle;
        free(current);
        --me->nSubscribers;
        return 1;
    }

    // Traverse the list to find the target element
    while (current != NULL) {
        // If the current element matches the target, update the previous element's next pointer and free the current element
        if (current->updateAddr == updateFuncAddr) {
            previous->itsNotificationHandle = current->itsNotificationHandle;
            free(current);
            --me->nSubscribers;
            return 1;
        }

        // Move on to the next element
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
