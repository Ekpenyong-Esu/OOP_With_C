//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_QRSDETECTOR_H
#define CLIENT_SERVER_PATTERN_QRSDETECTOR_H

#include "ECGPkg.h"
#include "TMDQueue.h"

// https://en.wikipedia.org/wiki/QRS_complex


typedef struct QRSDetector QRSDetector;
struct QRSDetector
{
    int heartRate;
    int index;
    struct TMDQueue* itsTMDQueue;
};

// constructions and desctructions
void QRSDetector_Init(QRSDetector* const self);
void QRSDetector_Cleanup(QRSDetector* const self);

void QRSDetector_computeHR(QRSDetector* const self);
void QRSDetector_getDataSample(QRSDetector* const self);
void QRSDetector_setItsTMDQueue(QRSDetector* const self, struct TMDQueue* p_TMDQueue);
struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const self);

QRSDetector * QRSDetector_Create(void);
QRSDetector * QRSDetector_Destroy(QRSDetector* const self);




#endif //CLIENT_SERVER_PATTERN_QRSDETECTOR_H
