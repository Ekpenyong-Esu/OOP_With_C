#include <stdio.h>
#include <stdlib.h>

// Define function pointer type for device operations
typedef void (*DeviceOperation)(void);

// Abstract structure representing a device
typedef struct {
    DeviceOperation operate;
} Device;

// Concrete implementation of a sensor device
typedef struct {
    Device base;
} SensorDevice;

// Concrete implementation of an actuator device
typedef struct {
    Device base;
} ActuatorDevice;

// Function to operate a sensor device
void operateSensorDevice(void) {
    printf("Sensor device is collecting data.\n");
}

// Function to operate an actuator device
void operateActuatorDevice(void) {
    printf("Actuator device is performing an action.\n");
}

// Factory function to create a device based on the specified type
Device* createDevice(int deviceType) {
    switch (deviceType) {
        case 1:
            return (Device*)malloc(sizeof(SensorDevice));
        case 2:
            return (Device*)malloc(sizeof(ActuatorDevice));
        default:
            return NULL; // Invalid device type
    }
}

int main() {
    // Using the factory to create devices
    Device* sensor = createDevice(1);
    Device* actuator = createDevice(2);

    // Assigning device-specific operations
    if (sensor) {
        sensor->operate = operateSensorDevice;
        sensor->operate();
        free(sensor);
    }

    if (actuator) {
        actuator->operate = operateActuatorDevice;
        actuator->operate();
        free(actuator);
    }

    return 0;
}
