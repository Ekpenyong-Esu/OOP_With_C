//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "TMDQueue.h"

static void initRelations(TMDQueue* const self);
static void cleanUpRelations(TMDQueue* const self);

void TMDQueue_Init(TMDQueue* const self) {
    self->head = 0;
    self->size = 0;
    initRelations(self);
}
void TMDQueue_Cleanup(TMDQueue* const self) {
    cleanUpRelations(self);
}
/* operation getNextIndex(int) */
int TMDQueue_getNextIndex(TMDQueue* const self, int index) {
    /* this operation computes the next index from the first using modulo arithmetic
    */
    return (index + 1) % QUEUE_SIZE;
}
/* operation insert(TimeMarkedData) */
void TMDQueue_insert(TMDQueue* const self, const struct TimeMarkedData tmd) {
    /* note that because we never ’remove’ data from this leaky queue, size only increases to
    the queue size and then stops increasing. Insertion always takes place at the head.
    */
    printf("Inserting at: %d Data #: %ld", self->head, tmd.timeInterval);
    self->buffer[self->head] = tmd;
    self->head = TMDQueue_getNextIndex(self, self->head);
    if (self->size < QUEUE_SIZE) {
        ++self->size;
        }
    printf(" Storing data value: %d\n", tmd.dataValue);
}
/* operation isEmpty() */
int TMDQueue_isEmpty(TMDQueue* const self) {
    return (self->size == 0);
}
/* operation remove(int) */
struct TimeMarkedData TMDQueue_remove(TMDQueue* const self, int index) {
    TimeMarkedData tmd;
    tmd.timeInterval = -1; /* sentinel values */
    tmd.dataValue = -9999;
    if (!TMDQueue_isEmpty(self) &&
        (index >= 0) && (index < QUEUE_SIZE)
        && (index < self->size)) {
        tmd = self->buffer[index];
    }
    return tmd;
}

int TMDQueue_getBuffer(const TMDQueue* const self) {
    int iter = 0;
    return iter;
}
TMDQueue * TMDQueue_Create(void) {
    TMDQueue* self = (TMDQueue *) malloc(sizeof(TMDQueue));
    if (self != NULL){
        TMDQueue_Init(self);
    }
    return self;
}

void TMDQueue_Destroy(TMDQueue* const self) {
    if (self != NULL){
        TMDQueue_Cleanup(self);
    }
    free(self);
}

static void initRelations(TMDQueue* const self) {
    int iter = 0;
    while (iter < QUEUE_SIZE) {
        TimeMarkedData_Init(&((self->buffer)[iter]));
        TimeMarkedData_setItsTMDQueue(&((self->buffer)[iter]), self);
        iter++;
    }
}


static void cleanUpRelations(TMDQueue* const self) {
    {
        int iter = 0;
        while (iter < QUEUE_SIZE) {
            TimeMarkedData_Cleanup(&((self->buffer)[iter]));
            iter++;
        }
    }
}
