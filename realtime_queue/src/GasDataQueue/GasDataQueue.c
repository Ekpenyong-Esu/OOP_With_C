#include "GasDataQueue.h"
#include <stdlib.h>

void GasDataQueue_Init(GasDataQueue* const me) {
    me->head = 0;
    me->tail = 0;
    me->count = 0;
}

void GasDataQueue_Cleanup(GasDataQueue* const me) {
    // Nothing to clean up for simple data structure
}

GasDataQueue* GasDataQueue_Create(void) {
    GasDataQueue* me = (GasDataQueue*) malloc(sizeof(GasDataQueue));
    if (me != NULL) {
        GasDataQueue_Init(me);
    }
    return me;
}

void GasDataQueue_Destroy(GasDataQueue* const me) {
    if (me != NULL) {
        GasDataQueue_Cleanup(me);
    }
    free(me);
}

unsigned char GasDataQueue_insert(GasDataQueue* const me, GasData data) {
    if (!me || me->count >= QUEUE_SIZE) {
        return 0;  // Queue full
    }
    
    me->queue[me->head] = data;  // Copy the data structure
    me->head = (me->head + 1) % QUEUE_SIZE;
    me->count++;
    
    return 1;  // Success
}

unsigned char GasDataQueue_remove(GasDataQueue* const me, GasData* data) {
    if (!me || !data || me->count == 0) {
        return 0;  // Queue empty or invalid parameters
    }
    
    *data = me->queue[me->tail];  // Copy out the data
    me->tail = (me->tail + 1) % QUEUE_SIZE;
    me->count--;
    
    return 1;  // Success
}

unsigned char GasDataQueue_isEmpty(const GasDataQueue* const me) {
    return (!me || me->count == 0) ? 1 : 0;
}

unsigned char GasDataQueue_isFull(const GasDataQueue* const me) {
    return (me && me->count >= QUEUE_SIZE) ? 1 : 0;
}
