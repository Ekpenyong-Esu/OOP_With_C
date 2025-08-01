#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep

// Include sensor headers
#include "OpticalSpeedSensor/OpticalSpeedSensor.h"
#include "DopplerSpeedSensors/DopplerSpeedSensor.h"
#include "GPSPositionSensors/GPSPositionSensor.h"
#include "SensorMasterModule/SensorMaster.h"
#include "Position.h"

int main() {
    printf("\nVehicle Sensor System\n");
    printf("====================\n\n");

    // Create sensor components
    OpticalSpeedSensor* opticalSensor = OpticalSpeedSensor_Create();
    DopplerSpeedSensor* dopplerSensor = DopplerSpeedSensor_Create();
    GPSPositionSensor* gpsSensor = GPSPositionSensor_Create();
    SensorMaster* sensorMaster = SensorMaster_Create();

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

    // Initialize sensor components
    if (!opticalSensor || !dopplerSensor || !gpsSensor || !sensorMaster) {
        printf("Failed to create sensor components\n");
        goto cleanup;
    }

    // Configure sensors
    OpticalSpeedSensor_configure(opticalSensor, 17, 5);  // 17" wheel size, sensitivity 5
    DopplerSpeedSensor_configure(dopplerSensor, 1000);   // 1000Hz sample rate
    GPSPositionSensor_configure(gpsSensor, 4, 1);        // Require 4 satellites, fast mode

    // Set up SensorMaster relationships
    SensorMaster_setItsDopplerSpeedSensor(sensorMaster, dopplerSensor);
    SensorMaster_setItsGPSPositionSensor(sensorMaster, gpsSensor);
    SensorMaster_setItsOpticalSpeedSensor(sensorMaster, opticalSensor);

    // Enable/activate sensors
    SensorMaster_doppler_enable(sensorMaster);
    SensorMaster_optical_enable(sensorMaster);
    SensorMaster_gps_activate(sensorMaster);

    // Main measurement loop
    printf("Starting vehicle sensor measurements...\n\n");
    for (int i = 0; i < 10; i++) {
        printf("Measurement %d:\n", i + 1);
        
        // Get speed from both sensors
        double dopplerSpeed = SensorMaster_doppler_getSpeed(sensorMaster);
        double opticalSpeed = SensorMaster_optical_getSpeed(sensorMaster);
        
        // Get GPS position
        Position position = SensorMaster_gps_getPosition(sensorMaster);

        // Display results
        printf("Doppler Speed: %.2f km/h\n", dopplerSpeed);
        printf("Optical Speed: %.2f km/h\n", opticalSpeed);
        printf("GPS Position: (%d, %d)\n\n", position.x, position.y);
        
        sleep(1);  // Wait a second between measurements
    }

    // Disable/deactivate sensors
    SensorMaster_doppler_disable(sensorMaster);
    SensorMaster_optical_disable(sensorMaster);
    SensorMaster_gps_deactivate(sensorMaster);

cleanup:
    // Clean up all components
    if (sensorMaster) SensorMaster_Destroy(sensorMaster);
    if (dopplerSensor) DopplerSpeedSensor_Destroy(dopplerSensor);
    if (gpsSensor) GPSPositionSensor_Destroy(gpsSensor);
    if (opticalSensor) OpticalSpeedSensor_Destroy(opticalSensor);
    if (queue) GasDataQueue_Destroy(queue);
    if (controller) GasController_Destroy(controller);
    if (display) GasDisplay_Destroy(display);

    return 0;
}
