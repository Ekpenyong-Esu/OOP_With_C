//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "HistogramDisplay.h"
#include "TMDQueue.h"

static void cleanUpRelations(HistogramDisplay* const self);


void HistogramDisplay_update(HistogramDisplay* const me, const struct TimeMarkedData tmd) {
    printf("    Histogram -> TimeInterval: %ld  DataValue: %d\n", tmd.timeInterval, tmd.dataValue);
}

void HistogramDisplay_Init(HistogramDisplay* const self) {
    self->itsTMDQueue = NULL;
    self->index = 0;  // Initialize index
}

void HistogramDisplay_Cleanup(HistogramDisplay* const me) {
    /* remove yourself from server subscription list */
    TMDQueue_unsubscribe(me->itsTMDQueue, HistogramDisplay_update);
    cleanUpRelations(me);
}

/* operation getValue() */
void HistogramDisplay_getValue(HistogramDisplay* const self) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("Histogram index: %d TimeInterval: %ld DataValue:%d\n", self->index, tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

void HistogramDisplay_updateHistogram(HistogramDisplay* const me) {

}

struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
    if (p_TMDQueue != NULL) {
        TMDQueue_subscribe(p_TMDQueue, HistogramDisplay_update);
    }
}

HistogramDisplay * HistogramDisplay_Create(void) {
    HistogramDisplay* me = (HistogramDisplay *) malloc(sizeof(HistogramDisplay));
    if(me!=NULL)
    {
        HistogramDisplay_Init(me);
    }
    return me;
}

void HistogramDisplay_Destroy(HistogramDisplay* const me) {
    if(me!=NULL)
    {
        HistogramDisplay_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(HistogramDisplay* const me) {
    if(me->itsTMDQueue != NULL)
    {
        me->itsTMDQueue = NULL;
    }
}
