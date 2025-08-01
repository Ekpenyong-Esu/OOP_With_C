#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep

// Include all required headers
#include "GasData/GasData.h"
#include "GasController/GasController.h"
#include "GasDisplay/GasDisplay.h"
#include "SensorThread/SensorThread.h"
#include "GasDataQueue/GasDataQueue.h"

int main() {
    printf("\nGas Monitoring System\n");
    printf("===================\n\n");

    // Create components
    GasDisplay* display = GasDisplay_Create();
    GasController* controller = GasController_Create();
    GasDataQueue* queue = GasDataQueue_Create();
    SensorThread* sensorThread = SensorThread_Create();

    if (!display || !controller || !queue || !sensorThread) {
        printf("Failed to create system components\n");
        goto cleanup;
    }

    // Set up component relationships
    GasController_setItsGasDisplay(controller, display);
    SensorThread_setItsGasDataQueue(sensorThread, queue);

    // Main simulation loop
    printf("Starting gas monitoring simulation...\n\n");
    for (int i = 0; i < 10; i++) {  // Run for 10 cycles
        printf("Cycle %d:\n", i + 1);
        
        // Update sensors and collect data
        SensorThread_updateData(sensorThread);

        // Process all data in queue
        GasData data;
        while (GasDataQueue_remove(queue, &data)) {
            GasController_handleGasData(controller, &data);
        }

        printf("\n");
        sleep(1);  // Wait a second between cycles
    }

cleanup:
    // Clean up all components
    if (sensorThread) SensorThread_Destroy(sensorThread);
    if (queue) GasDataQueue_Destroy(queue);
    if (controller) GasController_Destroy(controller);
    if (display) GasDisplay_Destroy(display);

    return 0;
}
