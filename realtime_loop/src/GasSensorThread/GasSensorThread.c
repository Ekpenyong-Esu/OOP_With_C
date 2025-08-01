// Refactored for readability and maintainability

#include "GasSensorThread.h"
#include <stdlib.h>
#include <time.h>

// Sensor data structure to hold current readings
typedef struct {
    int gasLevel;          // Current gas level (0-100)
    float temperature;     // Current temperature (Celsius)
    float pressure;        // Current pressure (kPa)
    int isInitialized;     // Flag to track initialization status
    int sensorHealth;      // Health status of sensors (0-100)
} SensorData;

// Static storage for sensor readings
static SensorData sensorData = {
    .gasLevel = 0,
    .temperature = 25.0f,
    .pressure = 101.3f,
    .isInitialized = 0,
    .sensorHealth = 100
};

/**
 * @brief Read the raw gas level from the sensor hardware
 * 
 * Simulates hardware interaction by generating random data.
 * 
 * @return int Raw gas level reading
 */
static int readRawGasLevel(void) {
    return rand() % 101;  // Simulate a gas level between 0 and 100
}

/**
 * @brief Read the raw temperature from the sensor hardware
 * 
 * Simulates hardware interaction by generating random data.
 * 
 * @return float Raw temperature reading
 */
static float readRawTemperature(void) {
    return (rand() % 151) / 10.0f - 10.0f;  // Simulate temperature between -10.0 and 15.0
}

/**
 * @brief Read the raw pressure from the sensor hardware
 * 
 * Simulates hardware interaction by generating random data.
 * 
 * @return float Raw pressure reading
 */
static float readRawPressure(void) {
    return 90.0f + (rand() % 210) / 10.0f;  // Simulate pressure between 90.0 and 110.0
}

/**
 * @brief Process sensor readings and update the sensor data structure
 */
static void processSensorReadings(void) {
    int rawGasLevel = readRawGasLevel();
    float rawTemperature = readRawTemperature();
    float rawPressure = readRawPressure();

    // Apply simple low-pass filtering
    const float alpha = 0.7f;  // Filter constant

    sensorData.gasLevel = (int)((alpha * sensorData.gasLevel) + (1.0f - alpha) * rawGasLevel);
    sensorData.temperature = (alpha * sensorData.temperature) + (1.0f - alpha) * rawTemperature;
    sensorData.pressure = (alpha * sensorData.pressure) + (1.0f - alpha) * rawPressure;
}

/**
 * @brief Run the gas sensor operations for one cycle
 */
void GasSensorThread_run(void) {
    if (!sensorData.isInitialized) return;

    // Read and process the sensor data
    processSensorReadings();

    // Check sensor health
    if (sensorData.gasLevel < 0 || sensorData.gasLevel > 100 ||
        sensorData.temperature < -10 || sensorData.temperature > 100 ||
        sensorData.pressure < 90 || sensorData.pressure > 110) {
        sensorData.sensorHealth -= 5;
        if (sensorData.sensorHealth < 0) sensorData.sensorHealth = 0;
    } else {
        if (sensorData.sensorHealth < 100) sensorData.sensorHealth += 1;
    }
}

/**
 * @brief Initialize the gas sensor subsystem
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasSensorThread_init(void) {
    srand((unsigned int)time(NULL));  // Seed the random number generator

    // Initialize sensor data
    sensorData.gasLevel = 50;
    sensorData.temperature = 25.0f;
    sensorData.pressure = 101.3f;
    sensorData.sensorHealth = 100;
    sensorData.isInitialized = 1;

    return 0;  // Success
}

/**
 * @brief Shutdown the gas sensor subsystem
 */
void GasSensorThread_shutdown(void) {
    sensorData.isInitialized = 0;
}

/**
 * @brief Get the current gas level reading
 * 
 * @return int The current gas level measurement (0-100)
 */
int GasSensorThread_getGasLevel(void) {
    return sensorData.gasLevel;
}

/**
 * @brief Get the current gas temperature reading
 * 
 * @return float The current gas temperature in degrees Celsius
 */
float GasSensorThread_getTemperature(void) {
    return sensorData.temperature;
}

/**
 * @brief Get the current gas pressure reading
 * 
 * @return float The current gas pressure in kPa
 */
float GasSensorThread_getPressure(void) {
    return sensorData.pressure;
}
