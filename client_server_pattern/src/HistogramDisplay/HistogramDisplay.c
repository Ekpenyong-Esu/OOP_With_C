//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "HistogramDisplay.h"

static void cleanUpRelations(HistogramDisplay* const self);

void HistogramDisplay_Init(HistogramDisplay* const self) {
    self->index = 0;
    self->itsTMDQueue = NULL;
}

void HistogramDisplay_Cleanup(HistogramDisplay* const self) {
    cleanUpRelations(self);
}

/* operation getValue() */
void HistogramDisplay_getValue(HistogramDisplay* const self) {
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("Histogram index: %d TimeInterval: %ld DataValue:%d\n", self->index, tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

/* operation updateHistogram() */
void HistogramDisplay_updateHistogram(HistogramDisplay* const self) {
    /* put some histogram stuff here... */
    printf("Updating histogram...\n");
    (void)self;
}

struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const self) {
    return (struct TMDQueue*)self->itsTMDQueue;
}

void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const self, struct TMDQueue* p_TMDQueue) {
    self->itsTMDQueue = p_TMDQueue;
}

HistogramDisplay * HistogramDisplay_Create(void) {
    HistogramDisplay* self = (HistogramDisplay *) malloc(sizeof(HistogramDisplay));
    if (self != NULL) {
        HistogramDisplay_Init(self);
    }
    return self;
}

void HistogramDisplay_Destroy(HistogramDisplay* const self) {
    if (self != NULL) {
        HistogramDisplay_Cleanup(self);
    }
    free(self);
}

static void cleanUpRelations(HistogramDisplay* const self) {
    if (self->itsTMDQueue != NULL) {
        self->itsTMDQueue = NULL;
    }

}
