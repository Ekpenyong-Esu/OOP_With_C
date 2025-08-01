//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_ECG_MODULE_H
#define CLIENT_SERVER_PATTERN_ECG_MODULE_H

#include "ECGPkg.h"
#include "TMDQueue.h"

/**
 * ECG_Module - Data Provider for the Observer Pattern
 * 
 * This module generates ECG data and sends it to the TMDQueue subject,
 * which then notifies all observers of the new data.
 */

typedef struct ECG_Module ECG_Module;
struct ECG_Module {
    int dataNum;                  // Counter for data samples
    int lead1;                    // ECG lead 1 selection
    int lead2;                    // ECG lead 2 selection
    struct TMDQueue* itsTMDQueue; // Subject that notifies observers
};

/* Constructors and destructors:*/
void ECG_Module_Init(ECG_Module* const self);
void ECG_Module_Cleanup(ECG_Module* const self);

/* Operations */

void ECG_Module_acquireValue(ECG_Module* const self);
void ECG_Module_setLeadPair(ECG_Module* const self, int lead1, int lead2);
struct TMDQueue* ECG_Module_getItsTMDQueue(const ECG_Module* const self);
void ECG_Module_setItsTMDQueue(ECG_Module* const self, struct TMDQueue* p_TMDQueue);
ECG_Module * ECG_Module_Create(void);
void ECG_Module_Destroy(ECG_Module* const self);

#endif //CLIENT_SERVER_PATTERN_ECG_MODULE_H
