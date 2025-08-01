#ifndef REALTIME_QUEUE_GASCONTOLLER_H
#define REALTIME_QUEUE_GASCONTOLLER_H

#include "GasData.h"
#include "GasDataQueue.h"

// Simple gas controller that processes gas data from the queue
typedef struct {
    GasDataQueue* queue;  // Queue of gas data to process
} GasController;

// Controller operations
GasController* GasController_create(void);
void GasController_destroy(GasController* controller);

// Process all gas data in queue
void GasController_process_data(GasController* controller);

// Add new gas data to process
int GasController_add_data(GasController* controller, GasData* data);

#endif
