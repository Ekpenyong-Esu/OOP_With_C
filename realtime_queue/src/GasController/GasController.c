#include "GasController.h"
#include <stdio.h>

GasController* GasController_create(void) {
    GasController* controller = (GasController*)malloc(sizeof(GasController));
    if (controller) {
        controller->queue = GasDataQueue_create();
    }
    return controller;
}

void GasController_destroy(GasController* controller) {
    if (!controller) return;
    
    if (controller->queue) {
        GasDataQueue_destroy(controller->queue);
    }
    free(controller);
}

void GasController_process_data(GasController* controller) {
    if (!controller || !controller->queue) return;
    
    // Process all data in queue
    while (!GasDataQueue_is_empty(controller->queue)) {
        GasData* data = GasDataQueue_pop(controller->queue);
        if (data) {
            GasData_print(data);  // Print the gas reading
            GasData_destroy(data);
        }
    }
}

int GasController_add_data(GasController* controller, GasData* data) {
    if (!controller || !controller->queue || !data) return 0;
    return GasDataQueue_push(controller->queue, data);
}
