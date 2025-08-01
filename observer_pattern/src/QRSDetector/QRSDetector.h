//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_QRSDETECTOR_H
#define CLIENT_SERVER_PATTERN_QRSDETECTOR_H

#include "ECGPkg.h"
#include "TMDQueue.h"

/**
 * Observer Pattern: OBSERVER class
 *
 * QRSDetector is another observer in the Observer pattern.
 * It analyzes ECG data to detect QRS complexes (key features in ECG signals).
 * See: https://en.wikipedia.org/wiki/QRS_complex
 */

typedef struct QRSDetector QRSDetector;
struct QRSDetector
{
    int heartRate;               // Computed heart rate 
    int index;                   // Current position in the queue
    struct TMDQueue* itsTMDQueue; // Reference to the subject
};

/**
 * Initialize the QRSDetector observer
 */
void QRSDetector_Init(QRSDetector* const self);

/**
 * Clean up the QRSDetector observer
 */
void QRSDetector_Cleanup(QRSDetector* const self);

/**
 * Observer Pattern: UPDATE method
 * 
 * Called by the subject when there is new data
 */
void QRSDetector_update(void* instance, const struct TimeMarkedData tmd);

/**
 * Compute heart rate based on QRS detection
 */
void QRSDetector_computeHR(QRSDetector* const self);

/**
 * Get a data sample from the subject's queue
 */
void QRSDetector_getDataSample(QRSDetector* const self);

/**
 * Observer Pattern: Connect observer to subject
 * 
 * This method:
 * 1. Sets a reference to the subject (TMDQueue)
 * 2. Subscribes to notifications from the subject
 */
void QRSDetector_setItsTMDQueue(QRSDetector* const self, struct TMDQueue* p_TMDQueue);

/**
 * Get reference to the subject
 */
struct TMDQueue* QRSDetector_getItsTMDQueue(const QRSDetector* const self);

/**
 * Create a new QRSDetector observer
 */
QRSDetector* QRSDetector_Create(void);
QRSDetector * QRSDetector_Destroy(QRSDetector* const self);




#endif //CLIENT_SERVER_PATTERN_QRSDETECTOR_H
