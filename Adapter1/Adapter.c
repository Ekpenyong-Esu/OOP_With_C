#include <stdio.h>
#include <stdlib.h>

// Modern system expects temperature in Fahrenheit
typedef struct {
    float (*get_temperature_fahrenheit)(void* self);
} ModernTempSensor;

// Legacy sensor only provides Celsius
typedef struct {
    float (*get_temperature_celsius)(void* self);
} LegacyTempSensor;

// Concrete legacy sensor implementation
typedef struct {
    LegacyTempSensor interface;
    float current_temp;
} ConcreteLegacySensor;

float legacy_sensor_get_celsius(void* self) {
    ConcreteLegacySensor* sensor = (ConcreteLegacySensor*)self;
    // Simulate reading from actual sensor
    return sensor->current_temp;
}

ConcreteLegacySensor* create_legacy_sensor() {
    ConcreteLegacySensor* sensor = malloc(sizeof(ConcreteLegacySensor));
    sensor->interface.get_temperature_celsius = legacy_sensor_get_celsius;
    sensor->current_temp = 25.0; // Example initial temperature in Celsius
    return sensor;
}

// Adapter to make legacy sensor work with modern system
typedef struct {
    ModernTempSensor interface;
    LegacyTempSensor* legacy_sensor;
} TempSensorAdapter;

float adapter_get_fahrenheit(void* self) {
    TempSensorAdapter* adapter = (TempSensorAdapter*)self;
    // Get Celsius reading from legacy sensor
    float celsius = adapter->legacy_sensor->get_temperature_celsius(adapter->legacy_sensor);
    // Convert to Fahrenheit
    return (celsius * 9.0/5.0) + 32.0;
}

TempSensorAdapter* create_adapter(LegacyTempSensor* legacy_sensor) {
    TempSensorAdapter* adapter = malloc(sizeof(TempSensorAdapter));
    adapter->interface.get_temperature_fahrenheit = adapter_get_fahrenheit;
    adapter->legacy_sensor = legacy_sensor;
    return adapter;
}

// Example modern system that expects Fahrenheit
void process_temperature(ModernTempSensor* sensor) {
    float temp_f = sensor->get_temperature_fahrenheit(sensor);
    printf("Current temperature: %.1f°F\n", temp_f);
    
    // Example temperature-based actions
    if (temp_f > 90.0) {
        printf("WARNING: High temperature detected!\n");
    } else if (temp_f < 32.0) {
        printf("WARNING: Freezing temperature detected!\n");
    } else {
        printf("Temperature is within normal range.\n");
    }
}

int main() {
    // Create legacy sensor
    ConcreteLegacySensor* legacy_sensor = create_legacy_sensor();
    
    // Create adapter to make it compatible with modern system
    TempSensorAdapter* adapter = create_adapter((LegacyTempSensor*)legacy_sensor);
    
    // Use the adapter with modern system
    process_temperature((ModernTempSensor*)adapter);
    
    // Simulate temperature change
    legacy_sensor->current_temp = 35.0;  // Hot day in Celsius
    process_temperature((ModernTempSensor*)adapter);
    
    // Clean up
    free(adapter);
    free(legacy_sensor);
    
    return 0;
}