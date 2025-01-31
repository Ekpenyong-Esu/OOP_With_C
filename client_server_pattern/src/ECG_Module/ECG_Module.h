//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_ECG_MODULE_H
#define CLIENT_SERVER_PATTERN_ECG_MODULE_H

#include "ECGPkg.h"
#include "TMDQueue.h"


/* class ECG_Module */

typedef struct ECG_Module ECG_Module;
struct ECG_Module {
    int dataNum;
    int lead1;
    int lead2;
    struct TMDQueue* itsTMDQueue;
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
