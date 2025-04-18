#include "GasSensorThread.h"
#include <stdlib.h>
#include <time.h>

/**
 * Sensor data structure to hold current readings
 */
typedef struct {
    int gasLevel;          // Current gas level (0-100)
    float temperature;     // Current temperature (Celsius)
    float pressure;        // Current pressure (kPa)
    int isInitialized;     // Flag to track initialization status
    int sensorHealth;      // Health status of sensors (0-100)
} SensorData;

/**
 * Static storage for sensor readings
 */
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
 * In a real system, this would interface with actual hardware.
 * For simulation, we generate data with some noise.
 * 
 * @return int Raw gas level reading
 */
static int readRawGasLevel(void) {
    // Simulate a sensor reading with some random noise
    // In a real system, this would read from ADC, I2C, etc.
    
    // Base level (for simulation purposes)
    static int baseLevel = 50;
    
    // Add some random noise (+/- 5 units)
    int noise = (rand() % 11) - 5;
    
    // Slowly drift the base level (for simulation)
    if (rand() % 10 == 0) {
        baseLevel += (rand() % 3) - 1;
        if (baseLevel < 10) baseLevel = 10;
        if (baseLevel > 90) baseLevel = 90;
    }
    
    return baseLevel + noise;
}

/**
 * @brief Read the raw temperature from the sensor hardware
 * 
 * @return float Raw temperature reading in Celsius
 */
static float readRawTemperature(void) {
    // Simulate a temperature reading
    static float baseTemp = 25.0f;
    
    // Add some random noise (+/- 0.5 degrees)
    float noise = ((float)(rand() % 11) - 5.0f) / 10.0f;
    
    return baseTemp + noise;
}

/**
 * @brief Read the raw pressure from the sensor hardware
 * 
 * @return float Raw pressure reading in kPa
 */
static float readRawPressure(void) {
    // Simulate a pressure reading (around 101.3 kPa = 1 atm)
    static float basePressure = 101.3f;
    
    // Add some random noise (+/- 0.3 kPa)
    float noise = ((float)(rand() % 7) - 3.0f) / 10.0f;
    
    return basePressure + noise;
}

/**
 * @brief Process the raw sensor readings and update the sensor data
 * 
 * Applies filtering, calibration, and other processing to raw readings
 */
static void processSensorReadings(void) {
    // Read raw values
    int rawGasLevel = readRawGasLevel();
    float rawTemperature = readRawTemperature();
    float rawPressure = readRawPressure();
    
    // Apply simple low-pass filtering (in a real system, more sophisticated
    // filtering, calibration and validation would be applied)
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
    
    // Check sensor health (in a real system this would be more extensive)
    // For demo, we just make sure values are in reasonable ranges
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

/**
 * @brief Initialize the gas sensor subsystem
 * 
 * @return int 0 on success, non-zero error code otherwise
 */
int GasSensorThread_init(void) {
    // Seed the random number generator for our simulated readings
    srand((unsigned int)time(NULL));
    
    // Initialize hardware - in a real system, this would configure ADCs, I2C, etc.
    // For simulation, we just initialize our data structure
    
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
    // In a real system, this would power down sensors, close device handles, etc.
    sensorData.isInitialized = 0;
}