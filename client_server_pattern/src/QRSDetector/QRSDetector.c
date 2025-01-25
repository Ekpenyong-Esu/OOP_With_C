//
// Created by mahon on 12/27/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "QRSDetector.h"

static void cleanUpRelations(QRSDetector* const self);

void QRSDetector_Init(QRSDetector* const self){
    self->heartRate = 0;
    self->index = 0;
    self->itsTMDQueue = NULL;
}

void QRSDetector_Cleanup(QRSDetector* const self){
    cleanUpRelations(self);
}

void QRSDetector_computeHR(QRSDetector* const self){
    self->heartRate = self->heartRate + 10;
}

void QRSDetector_getDataSample(QRSDetector* const self){
    TimeMarkedData tmd;
    tmd = TMDQueue_remove(self->itsTMDQueue, self->index);
    printf("QRSDetector index: %d TimeInterval: %d  DataValue: %d\n", self->index, tmd.timeInterval, tmd.dataValue);
    self->index = TMDQueue_getNextIndex(self->itsTMDQueue, self->index);
}

void QRSDetector_setItsTMDQueue(QRSDetector* const self, struct TMDQueue* p_TMDQueue){
    self->itsTMDQueue = p_TMDQueue;
}

struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const self){
    return self->itsTMDQueue;
}

QRSDetector * QRSDetector_Create(void){
    QRSDetector* self = (QRSDetector*)malloc(sizeof(QRSDetector));
    if (self != NULL)
    {
        QRSDetector_Init(self);
    }
    return self;
}

QRSDetector * QRSDetector_Destroy(QRSDetector* const self){
    if (self != NULL)
    {
        QRSDetector_Cleanup(self);
    }
    free(self);
}

static void cleanUpRelations(QRSDetector* const self) {
    if (self->itsTMDQueue != NULL) {
        self->itsTMDQueue = NULL;
    }
}
