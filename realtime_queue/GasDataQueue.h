//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_GASDATAQUEUE_H
#define REALTIME_QUEUE_GASDATAQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "QueuingExample.h"
#include "GasData.h"
#include "OSSemaphore.h"

typedef struct GasDataQueue GasDataQueue;
struct GasDataQueue {
    int head;
    OSSemaphore * sema;
    int size;
    int tail;
    struct GasData itsGasData[GAS_QUEUE_SIZE];
};

/* Constructors and destructors:*/

void GasDataQueue_Init(GasDataQueue* const me);
void GasDataQueue_Cleanup(GasDataQueue* const me);

/* Operations */
int GasDataQueue_insert(GasDataQueue* const me, GasData g);

GasData * GasDataQueue_remove(GasDataQueue* const me);

int GasDataQueue_getItsGasData(const GasDataQueue* const me);

GasDataQueue * GasDataQueue_Create(void);

void GasDataQueue_Destroy(GasDataQueue* const me);

#endif //REALTIME_QUEUE_GASDATAQUEUE_H
