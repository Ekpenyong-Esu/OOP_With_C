#include <stdio.h>
#include <stdlib.h>
#include "../src/ResourceManager/ResourceList.h"
#include "../src/VelocityManager/Velocity.h"
#include "../src/VelocitySensors/VelocitySensor.h"

int main(int argc, char *argv[]) {
    printf("Real-time Order Lock System\n");
    printf("---------------------------\n");

    // Initialize components
    ResourceList* resourceList = ResourceList_Create();
    if (!resourceList) {
        fprintf(stderr, "Failed to create resource list\n");
        return EXIT_FAILURE;
    }

    // Initialize velocity management
    Velocity velocity = {0};  // Initialize velocity structure
    VelocitySensor* sensor = VelocitySensor_Create();
    if (!sensor) {
        fprintf(stderr, "Failed to create velocity sensor\n");
        ResourceList_Destroy(resourceList);
        return EXIT_FAILURE;
    }

    // Main application loop
    printf("System initialized successfully!\n");
    printf("Press Ctrl+C to exit\n");

    while (1) {
        // Update velocity readings
        VelocitySensor_Update(sensor, &velocity);

        // Process resource list
        ResourceList_Process(resourceList);

        // Add a small delay to prevent CPU hogging
        usleep(100000);  // 100ms delay
    }

    // Cleanup (Note: This won't be reached in this example due to infinite loop)
    VelocitySensor_Destroy(sensor);
    ResourceList_Destroy(resourceList);

    return EXIT_SUCCESS;
}
