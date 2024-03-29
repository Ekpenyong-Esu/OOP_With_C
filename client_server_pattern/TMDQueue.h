//
// Created by mahon on 12/27/2023.
//

#ifndef CLIENT_SERVER_PATTERN_TMDQUEUE_H
#define CLIENT_SERVER_PATTERN_TMDQUEUE_H

#include <stdio.h>
#include "ECGPkg.h"
#include "TimeMarkedData.h"

typedef struct TMDQueue TMDQueue;

struct TMDQueue {
    int head;
    int size;
    TimeMarkedData buffer[100];
};
/* Constructors and destructors:*/
void TMDQueue_Init(TMDQueue* const me);
void TMDQueue_Cleanup(TMDQueue* const me);

/* Operations */
int  TMDQueue_getNextIndex(TMDQueue* const me, int index);
void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd);
int  TMDQueue_isEmpty(TMDQueue* const me);
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index);
int  TMDQueue_getBuffer(const TMDQueue* const me);

TMDQueue * TMDQueue_Create(void);
void TMDQueue_Destroy(TMDQueue* const me);


#endif //CLIENT_SERVER_PATTERN_TMDQUEUE_H
