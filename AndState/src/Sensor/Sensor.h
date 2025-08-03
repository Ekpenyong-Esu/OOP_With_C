//
// Sensor Component - Demonstrates sensor-based AND pattern
// Shows how sensors can have multiple independent aspects:
// - Operational state (ON/OFF/CALIBRATING)
// - Reading quality (GOOD/POOR/INVALID)
// - Power mode (LOW/NORMAL/HIGH)
//

#ifndef ANDSTATE_SENSOR_H
#define ANDSTATE_SENSOR_H

#include <stdbool.h>

typedef enum SensorState {
    SENSOR_OFF,
    SENSOR_INITIALIZING,
    SENSOR_CALIBRATING,
    SENSOR_READY,
    SENSOR_ACTIVE,
    SENSOR_ERROR
} SensorState;

typedef enum DataQuality {
    QUALITY_INVALID,
    QUALITY_POOR,
    QUALITY_GOOD,
    QUALITY_EXCELLENT
} DataQuality;

typedef enum PowerMode {
    POWER_SLEEP,
    POWER_LOW,
    POWER_NORMAL,
    POWER_HIGH
} PowerMode;

typedef enum SensorType {
    TEMPERATURE_SENSOR,
    HUMIDITY_SENSOR,
    PRESSURE_SENSOR,
    LIGHT_SENSOR
} SensorType;

typedef struct Sensor Sensor;
struct Sensor {
    // AND Pattern: Multiple independent aspects
    SensorState state;          // Operational state
    DataQuality quality;        // Data quality assessment
    PowerMode power_mode;       // Power consumption mode
    SensorType type;           // What kind of sensor
    
    // Sensor data
    float current_value;        // Current sensor reading
    float min_value;           // Minimum valid value
    float max_value;           // Maximum valid value
    float calibration_offset;   // Calibration adjustment
    
    // Status tracking
    unsigned int error_count;   // Number of errors detected
    unsigned int sample_count;  // Total samples taken
    bool auto_calibrate;       // Automatic calibration enabled
    
    // Thresholds for quality assessment
    float noise_threshold;      // Above this is considered noisy
    float stability_threshold;  // Required for good quality
};

// Constructor/Destructor
void Sensor_Init(Sensor* const me, SensorType type, float min_val, float max_val);
void Sensor_Cleanup(Sensor* const me);
Sensor* Sensor_Create(SensorType type, float min_val, float max_val);
void Sensor_Destroy(Sensor* const me);

// Basic sensor operations
void Sensor_turnOn(Sensor* const me);
void Sensor_turnOff(Sensor* const me);
void Sensor_calibrate(Sensor* const me);
void Sensor_reset(Sensor* const me);

// AND Pattern operations - independent aspects
void Sensor_setPowerMode(Sensor* const me, PowerMode mode);
void Sensor_setAutoCalibrate(Sensor* const me, bool enable);
void Sensor_setThresholds(Sensor* const me, float noise_thresh, float stability_thresh);

// Data operations
bool Sensor_takeSample(Sensor* const me);  // Simulates taking a reading
float Sensor_getValue(Sensor* const me);
DataQuality Sensor_getQuality(Sensor* const me);
bool Sensor_isReady(Sensor* const me);

// Status and diagnostics
void Sensor_updateQuality(Sensor* const me);  // Assess data quality
void Sensor_displayStatus(Sensor* const me);
const char* Sensor_getStateString(Sensor* const me);
const char* Sensor_getQualityString(Sensor* const me);
const char* Sensor_getPowerModeString(Sensor* const me);
const char* Sensor_getTypeString(Sensor* const me);

// Statistics
float Sensor_getErrorRate(Sensor* const me);
unsigned int Sensor_getSampleCount(Sensor* const me);
void Sensor_resetStatistics(Sensor* const me);

#endif //ANDSTATE_SENSOR_H
