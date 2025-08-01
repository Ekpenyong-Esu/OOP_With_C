
#ifndef ARRHYTHMIA_DETECTOR_H
#define ARRHYTHMIA_DETECTOR_H

#include "ECGPkg.h"
#include "TMDQueue.h"

/**
 * Observer Pattern: OBSERVER class
 *
 * ArrhythmiaDetector is another observer in the Observer pattern.
 * It analyzes ECG data to detect various heart arrhythmias.
 */

typedef struct ArrhythmiaDetector ArrhythmiaDetector;
struct ArrhythmiaDetector
{
    int pcvCount;                // Premature ventricular contractions
    int STSegmentHeight;         // ST segment elevation/depression
    int firstDegreeHeatBlock;    // First-degree heart block
    int Two_one_heartBlock;      // 2:1 heart block
    int prematureAtrialContraction; // PAC count
    int flbrillation;            // Atrial fibrillation detected
    int index;                   // Current position in the queue
    struct TMDQueue* itsTMDQueue; // Reference to the subject
};

/**
 * Initialize the ArrhythmiaDetector observer
 */
void ArrhythmiaDetector_Init(ArrhythmiaDetector* const self);

/**
 * Clean up the ArrhythmiaDetector observer
 */
void ArrhythmiaDetector_Cleanup(ArrhythmiaDetector* const self);

/**
 * Observer Pattern: UPDATE method
 * 
 * Called by the subject when there is new data
 */
void ArrhythmiaDetector_update(void* instance, const struct TimeMarkedData tmd);

/**
 * Analyze ECG data to detect arrhythmias
 */
void ArrhythmiaDetector_indentifyArrhythmia(ArrhythmiaDetector* const self);

/**
 * Get a data sample from the subject's queue
 */
void ArrhythmiaDetector_getDataSample(ArrhythmiaDetector* const self);

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method:
 * 1. Sets a reference to the subject (TMDQueue)
 * 2. Subscribes to notifications from the subject
 */
void ArrhythmiaDetector_setItsTMDQueue(ArrhythmiaDetector* const self, struct TMDQueue* p_TMDQueue);

/**
 * Create a new ArrhythmiaDetector observer
 */
ArrhythmiaDetector* ArrhythmiaDetector_Create(void);

/**
 * Destroy the ArrhythmiaDetector observer
 */
ArrhythmiaDetector* ArrhythmiaDetector_Destroy(ArrhythmiaDetector* const self);

#endif
