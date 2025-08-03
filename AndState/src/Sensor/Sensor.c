//
// Sensor Component Implementation
//

#include "Sensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// Helper functions for string conversion
static const char* stateToString(SensorState state) {
    switch(state) {
        case SENSOR_OFF: return "OFF";
        case SENSOR_INITIALIZING: return "INITIALIZING";
        case SENSOR_CALIBRATING: return "CALIBRATING";
        case SENSOR_READY: return "READY";
        case SENSOR_ACTIVE: return "ACTIVE";
        case SENSOR_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

static const char* qualityToString(DataQuality quality) {
    switch(quality) {
        case QUALITY_INVALID: return "INVALID";
        case QUALITY_POOR: return "POOR";
        case QUALITY_GOOD: return "GOOD";
        case QUALITY_EXCELLENT: return "EXCELLENT";
        default: return "UNKNOWN";
    }
}

static const char* powerModeToString(PowerMode mode) {
    switch(mode) {
        case POWER_SLEEP: return "SLEEP";
        case POWER_LOW: return "LOW";
        case POWER_NORMAL: return "NORMAL";
        case POWER_HIGH: return "HIGH";
        default: return "UNKNOWN";
    }
}

static const char* typeToString(SensorType type) {
    switch(type) {
        case TEMPERATURE_SENSOR: return "TEMPERATURE";
        case HUMIDITY_SENSOR: return "HUMIDITY";
        case PRESSURE_SENSOR: return "PRESSURE";
        case LIGHT_SENSOR: return "LIGHT";
        default: return "UNKNOWN";
    }
}

// Simulate sensor reading based on type
static float simulateReading(SensorType type) {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }

    float base_value;
    float noise = ((rand() % 100) - 50) / 1000.0f;  // ±0.05 noise

    switch(type) {
        case TEMPERATURE_SENSOR:
            base_value = 20.0f + (rand() % 20);  // 20-40°C
            break;
        case HUMIDITY_SENSOR:
            base_value = 30.0f + (rand() % 50);  // 30-80%
            break;
        case PRESSURE_SENSOR:
            base_value = 1000.0f + (rand() % 100);  // 1000-1100 hPa
            break;
        case LIGHT_SENSOR:
            base_value = (float)(rand() % 1000);  // 0-1000 lux
            break;
        default:
            base_value = 0.0f;
    }

    return base_value + noise;
}

// Constructor/Destructor
void Sensor_Init(Sensor* const me, SensorType type, float min_val, float max_val) {
    if (me == NULL) return;

    me->state = SENSOR_OFF;
    me->quality = QUALITY_INVALID;
    me->power_mode = POWER_NORMAL;
    me->type = type;

    me->current_value = 0.0f;
    me->min_value = min_val;
    me->max_value = max_val;
    me->calibration_offset = 0.0f;

    me->error_count = 0;
    me->sample_count = 0;
    me->auto_calibrate = true;

    me->noise_threshold = 0.1f;
    me->stability_threshold = 0.05f;

    printf("Sensor initialized: %s sensor (%.1f - %.1f range)\n",
           typeToString(type), min_val, max_val);
}

void Sensor_Cleanup(Sensor* const me) {
    if (me == NULL) return;

    me->state = SENSOR_OFF;
    printf("Sensor cleaned up\n");
}

Sensor* Sensor_Create(SensorType type, float min_val, float max_val) {
    Sensor* me = (Sensor*)malloc(sizeof(Sensor));
    if (me != NULL) {
        Sensor_Init(me, type, min_val, max_val);
    }
    return me;
}

void Sensor_Destroy(Sensor* const me) {
    if (me != NULL) {
        Sensor_Cleanup(me);
        free(me);
    }
}

// Basic operations
void Sensor_turnOn(Sensor* const me) {
    if (me == NULL) return;

    me->state = SENSOR_INITIALIZING;
    printf("Sensor turning on...\n");

    // Simulate initialization time
    me->state = SENSOR_READY;
    me->quality = QUALITY_POOR;  // Start with poor quality

    printf("Sensor ready (%s)\n", typeToString(me->type));
}

void Sensor_turnOff(Sensor* const me) {
    if (me == NULL) return;

    me->state = SENSOR_OFF;
    me->quality = QUALITY_INVALID;

    printf("Sensor turned off\n");
}

void Sensor_calibrate(Sensor* const me) {
    if (me == NULL || me->state == SENSOR_OFF) {
        return;
    }

    me->state = SENSOR_CALIBRATING;
    printf("Calibrating sensor...\n");

    // Simulate calibration - adjust offset
    me->calibration_offset = (rand() % 20 - 10) / 100.0f;  // ±0.1 adjustment

    me->state = SENSOR_READY;
    printf("Calibration complete (offset: %.3f)\n", me->calibration_offset);
}

void Sensor_reset(Sensor* const me) {
    if (me == NULL) return;

    me->error_count = 0;
    me->sample_count = 0;
    me->calibration_offset = 0.0f;
    me->quality = QUALITY_INVALID;

    if (me->state != SENSOR_OFF) {
        me->state = SENSOR_READY;
    }

    printf("Sensor reset\n");
}

// AND Pattern operations - these can be changed independently
void Sensor_setPowerMode(Sensor* const me, PowerMode mode) {
    if (me == NULL) return;

    me->power_mode = mode;
    printf("Sensor power mode changed to: %s\n", powerModeToString(mode));

    // Power mode affects quality
    if (mode == POWER_SLEEP && me->state == SENSOR_ACTIVE) {
        me->state = SENSOR_READY;
    }
}

void Sensor_setAutoCalibrate(Sensor* const me, bool enable) {
    if (me == NULL) return;

    me->auto_calibrate = enable;
    printf("Auto-calibration: %s\n", enable ? "ENABLED" : "DISABLED");
}

void Sensor_setThresholds(Sensor* const me, float noise_thresh, float stability_thresh) {
    if (me == NULL) return;

    me->noise_threshold = noise_thresh;
    me->stability_threshold = stability_thresh;
    printf("Thresholds updated - Noise: %.3f, Stability: %.3f\n",
           noise_thresh, stability_thresh);
}

// Data operations
bool Sensor_takeSample(Sensor* const me) {
    if (me == NULL || me->state == SENSOR_OFF || me->power_mode == POWER_SLEEP) {
        return false;
    }

    me->state = SENSOR_ACTIVE;
    me->sample_count++;

    // Simulate taking a reading
    float raw_value = simulateReading(me->type);
    me->current_value = raw_value + me->calibration_offset;

    // Check if value is in valid range
    if (me->current_value < me->min_value || me->current_value > me->max_value) {
        me->error_count++;
        me->quality = QUALITY_INVALID;
        printf("Sample %d: ERROR - Value %.2f out of range\n",
               me->sample_count, me->current_value);
        return false;
    }

    // Update quality assessment
    Sensor_updateQuality(me);

    printf("Sample %d: %.2f (%s quality)\n",
           me->sample_count, me->current_value, qualityToString(me->quality));

    // Auto-calibrate if enabled and quality is poor
    if (me->auto_calibrate && me->quality == QUALITY_POOR &&
        me->sample_count % 10 == 0) {
        Sensor_calibrate(me);
    }

    me->state = SENSOR_READY;
    return true;
}

float Sensor_getValue(Sensor* const me) {
    return (me != NULL) ? me->current_value : 0.0f;
}

DataQuality Sensor_getQuality(Sensor* const me) {
    return (me != NULL) ? me->quality : QUALITY_INVALID;
}

bool Sensor_isReady(Sensor* const me) {
    return (me != NULL) &&
           (me->state == SENSOR_READY || me->state == SENSOR_ACTIVE) &&
           (me->power_mode != POWER_SLEEP);
}

// Quality assessment
void Sensor_updateQuality(Sensor* const me) {
    if (me == NULL || me->sample_count == 0) return;

    float error_rate = (float)me->error_count / (float)me->sample_count;

    // Simulate noise level based on power mode
    float noise_level = 0.0f;
    switch (me->power_mode) {
        case POWER_SLEEP:
        case POWER_LOW:
            noise_level = 0.15f;  // Higher noise in low power
            break;
        case POWER_NORMAL:
            noise_level = 0.05f;
            break;
        case POWER_HIGH:
            noise_level = 0.02f;  // Lower noise in high power
            break;
    }

    // Determine quality based on error rate and noise
    if (error_rate > 0.1f || noise_level > me->noise_threshold) {
        me->quality = QUALITY_INVALID;
    } else if (error_rate > 0.05f || noise_level > me->stability_threshold) {
        me->quality = QUALITY_POOR;
    } else if (error_rate > 0.01f) {
        me->quality = QUALITY_GOOD;
    } else {
        me->quality = QUALITY_EXCELLENT;
    }
}

// Display and status
void Sensor_displayStatus(Sensor* const me) {
    if (me == NULL) {
        printf("Sensor: NULL pointer\n");
        return;
    }

    printf("Sensor Status: %s | %s | Power: %s | Quality: %s\n",
           typeToString(me->type),
           stateToString(me->state),
           powerModeToString(me->power_mode),
           qualityToString(me->quality));

    if (me->sample_count > 0) {
        printf("  Value: %.2f | Samples: %d | Errors: %d (%.1f%%)\n",
               me->current_value,
               me->sample_count,
               me->error_count,
               Sensor_getErrorRate(me) * 100.0f);
    }
}

const char* Sensor_getStateString(Sensor* const me) {
    return (me != NULL) ? stateToString(me->state) : "NULL";
}

const char* Sensor_getQualityString(Sensor* const me) {
    return (me != NULL) ? qualityToString(me->quality) : "NULL";
}

const char* Sensor_getPowerModeString(Sensor* const me) {
    return (me != NULL) ? powerModeToString(me->power_mode) : "NULL";
}

const char* Sensor_getTypeString(Sensor* const me) {
    return (me != NULL) ? typeToString(me->type) : "NULL";
}

// Statistics
float Sensor_getErrorRate(Sensor* const me) {
    if (me == NULL || me->sample_count == 0) return 0.0f;
    return (float)me->error_count / (float)me->sample_count;
}

unsigned int Sensor_getSampleCount(Sensor* const me) {
    return (me != NULL) ? me->sample_count : 0;
}

void Sensor_resetStatistics(Sensor* const me) {
    if (me == NULL) return;

    me->error_count = 0;
    me->sample_count = 0;
    printf("Sensor statistics reset\n");
}
