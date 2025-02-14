
#ifndef ARRHYTHMIA_DETECTOR_H
#define ARRHYTHMIA_DETECTOR_H

#include "ECGPkg.h"
#include "TMDQueue.h"


typedef struct ArrhythmiaDetector ArrhythmiaDetector;
struct ArrhythmiaDetector
{
    int pcvCount;
    int STSegmentHeight;
    int firstDegreeHeatBlock;
    int Two_one_heartBlock;
    int prematureAtrialContraction;
    int flbrillation;
    int index;
    struct TMDQueue* itsTMDQueue;
};

// constructions and desctructions
void ArrhythmiaDetector_Init(ArrhythmiaDetector* const self);
void ArrhythmiaDetector_Cleanup(ArrhythmiaDetector* const self);

void ArrhythmiaDetector_indentifyArrhythmia(ArrhythmiaDetector* const self);
void ArrhythmiaDetector_getDataSample(ArrhythmiaDetector* const self);
void ArrhythmiaDetector_setItsTMDQueue(ArrhythmiaDetector* const self, struct TMDQueue* p_TMDQueue);

ArrhythmiaDetector * ArrhythmiaDetector_Create(void);
ArrhythmiaDetector * ArrhythmiaDetector_Destroy(ArrhythmiaDetector* const self);

#endif
