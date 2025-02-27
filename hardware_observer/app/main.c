#include <stdio.h>
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
int main(int argc, char const *argv[])
{
    printf("Hardware Observer Pattern Demonstration\n");
    printf("--------------------------------------\n\n");

    // Create the sensor (Subject/Observable)
    GasSensor* p_GasSensor = GasSensor_Create();
    
    // Create observer
    DisplayClient* p_DisplayClient = DisplayClient_Create();
    
    // Observer Pattern: Set up relationship between observer and subject
    DisplayClient_setItsGasSensor(p_DisplayClient, p_GasSensor);
    
    // Observer Pattern: Register observer with the subject
    DisplayClient_register(p_DisplayClient);
    
    // Simulate sensor readings
    printf("Starting hardware monitoring simulation...\n\n");
    for (int i = 0; i < 4; i++) {
        printf("Reading #%d:\n", i+1);
        
        // Observer Pattern: Update subject's state which triggers notification to observers
        GasSensor_readSensor(p_GasSensor);
        
        // In a real system, you might not need this delay
        sleep(1);
    }
    
    // Test alarm functionality
    DisplayClient_alarm(p_DisplayClient, "Gas flow rate exceeds threshold!");
    
    // Clean up
    DisplayClient_Destroy(p_DisplayClient);
    GasSensor_Destroy(p_GasSensor);
    
    return 0;
}
