#ifndef GAS_SENSOR_BASE_H
#define GAS_SENSOR_BASE_H

/**
 * @brief Common interface for all gas sensors
 */
typedef struct {
    double concentration;  // Gas concentration in percent
    double flowRate;      // Flow rate in CC/min
    int health;          // Sensor health (0-100)
    int isInitialized;   // Initialization status
} GasSensorBase;

// Standard interface functions all sensors must implement
void GasSensorBase_Init(GasSensorBase* const me);
void GasSensorBase_Cleanup(GasSensorBase* const me);
void GasSensorBase_Update(GasSensorBase* const me);  // Read new sensor data

// Optional calibration and diagnostic functions
int GasSensorBase_CheckHealth(GasSensorBase* const me);
void GasSensorBase_Calibrate(GasSensorBase* const me);

#endif /* GAS_SENSOR_BASE_H */
