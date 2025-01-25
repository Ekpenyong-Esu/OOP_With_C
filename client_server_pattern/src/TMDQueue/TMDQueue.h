//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TMDQUEUE_H
#define CLIENT_SERVER_PATTERN_TMDQUEUE_H

#include "ECGPkg.h"
#include "TimeMarkedData.h"

typedef struct TMDQueue TMDQueue;

struct TMDQueue {
    int head;
    int size;
    TimeMarkedData buffer[QUEUE_SIZE];
};
/* Constructors and destructors:*/
void TMDQueue_Init(TMDQueue* const self);
void TMDQueue_Cleanup(TMDQueue* const self);

/* Operations */
int  TMDQueue_getNextIndex(TMDQueue* const self, int index);
void TMDQueue_insert(TMDQueue* const self, const struct TimeMarkedData tmd);
int  TMDQueue_isEmpty(TMDQueue* const self);
struct TimeMarkedData TMDQueue_remove(TMDQueue* const self, int index);
int  TMDQueue_getBuffer(const TMDQueue* const self);

TMDQueue * TMDQueue_Create(void);
void TMDQueue_Destroy(TMDQueue* const self);


#endif //CLIENT_SERVER_PATTERN_TMDQUEUE_H
