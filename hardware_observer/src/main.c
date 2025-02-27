#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include "GasSensor.h"
#include "DisplayClient.h"

/**
 * Observer Pattern Demonstration
 * 
 * This example demonstrates the Observer pattern in C:
 * 1. GasSensor - Acts as the Subject (Observable)
 * 2. DisplayClient - Acts as the Observer
 * 3. GasData - Represents the state being observed
 */
int main() {
    // Create the sensor (Subject)
    GasSensor* sensor = GasSensor_Create();
    
    // Create observers (DisplayClients)
    DisplayClient* display1 = DisplayClient_Create();
    DisplayClient* display2 = DisplayClient_Create();
    
    printf("Hardware Observer Pattern Demonstration\n");
    printf("--------------------------------------\n\n");
    
    // Observer Pattern: Set up relationships between observers and subject
    DisplayClient_setItsGasSensor(display1, sensor);
    DisplayClient_setItsGasSensor(display2, sensor);
    
    // Observer Pattern: Register observers with the subject
    DisplayClient_register(display1);
    DisplayClient_register(display2);
    
    // Simulate sensor readings and notify observers
    printf("Starting hardware monitoring simulation...\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Reading #%d:\n", i+1);
        
        // Observer Pattern: Update subject's state, which triggers notification
        GasSensor_readSensor(sensor);
        
        // In a real system, you might not need this delay
        sleep(1);
    }
    
    // Test alarm functionality
    DisplayClient_alarm(display1, "Gas flow rate exceeds threshold!");
    
    // Clean up
    DisplayClient_Destroy(display1);
    DisplayClient_Destroy(display2);
    GasSensor_Destroy(sensor);
    
    return 0;
}
