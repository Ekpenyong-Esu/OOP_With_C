//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_QUEUE_GASDATAQUEUE_H
#define REALTIME_QUEUE_GASDATAQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "../GasData/GasData.h"

#define QUEUE_SIZE 10

typedef struct GasDataQueue GasDataQueue;
struct GasDataQueue {
    int head;           // Index for insertion
    int tail;           // Index for removal
    int count;          // Number of elements in queue
    GasData queue[QUEUE_SIZE];  // Circular buffer storing actual gas data
};

/* Constructor and destructor */
void GasDataQueue_Init(GasDataQueue* const me);
void GasDataQueue_Cleanup(GasDataQueue* const me);
GasDataQueue* GasDataQueue_Create(void);
void GasDataQueue_Destroy(GasDataQueue* const me);

/* Operations */
unsigned char GasDataQueue_insert(GasDataQueue* const me, GasData data);      // Returns 1 if successful, 0 if queue full
unsigned char GasDataQueue_remove(GasDataQueue* const me, GasData* data);     // Returns 1 if successful, 0 if queue empty

/* Queue state checks */
unsigned char GasDataQueue_isEmpty(const GasDataQueue* const me);
unsigned char GasDataQueue_isFull(const GasDataQueue* const me);

#endif //REALTIME_QUEUE_GASDATAQUEUE_H
