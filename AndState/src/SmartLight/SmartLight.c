//
// SmartLight Implementation - Complex AND Pattern Example
//

#include "SmartLight.h"
#include <stdlib.h>
#include <stdio.h>

// Helper string conversion functions
static const char* modeToString(SmartMode mode) {
    switch(mode) {
        case MANUAL_MODE: return "MANUAL";
        case AUTO_MODE: return "AUTO";
        case TIMER_MODE: return "TIMER";
        case ADAPTIVE_MODE: return "ADAPTIVE";
        default: return "UNKNOWN";
    }
}

static const char* brightnessToString(BrightnessLevel level) {
    switch(level) {
        case BRIGHTNESS_OFF: return "OFF";
        case BRIGHTNESS_DIM: return "DIM";
        case BRIGHTNESS_MEDIUM: return "MEDIUM";
        case BRIGHTNESS_BRIGHT: return "BRIGHT";
        case BRIGHTNESS_MAX: return "MAX";
        default: return "UNKNOWN";
    }
}

// Constructor/Destructor
void SmartLight_Init(SmartLight* const me) {
    if (me == NULL) return;
    
    // Create component instances
    me->light = Light_Create();
    me->auto_timer = Timer_Create(5000, ONESHOT);  // 5 second auto-off
    me->fade_timer = Timer_Create(1000, ONESHOT);  // 1 second fade
    me->light_sensor = Sensor_Create(LIGHT_SENSOR, 0.0f, 1000.0f);
    me->motion_sensor = Sensor_Create(PRESSURE_SENSOR, 0.0f, 1.0f);  // Using pressure as motion
    
    // Initialize SmartLight specific state
    me->mode = AUTO_MODE;
    me->brightness = BRIGHTNESS_MEDIUM;
    me->motion_enabled = true;
    me->auto_dimming = true;
    me->energy_saving = false;
    
    // Configuration defaults
    me->light_threshold = 100.0f;  // Turn on when ambient < 100 lux
    me->fade_duration = 1000;      // 1 second fade
    me->auto_timeout = 300000;     // 5 minutes auto-off
    
    // State tracking
    me->last_motion_state = false;
    me->last_light_level = 500.0f;
    me->manual_overrides = 0;
    
    // Start sensors
    if (me->light_sensor) Sensor_turnOn(me->light_sensor);
    if (me->motion_sensor) Sensor_turnOn(me->motion_sensor);
    
    printf("SmartLight initialized in %s mode\n", modeToString(me->mode));
}

void SmartLight_Cleanup(SmartLight* const me) {
    if (me == NULL) return;
    
    // Cleanup all components
    Light_Destroy(me->light);
    Timer_Destroy(me->auto_timer);
    Timer_Destroy(me->fade_timer);
    Sensor_Destroy(me->light_sensor);
    Sensor_Destroy(me->motion_sensor);
    
    printf("SmartLight cleaned up\n");
}

SmartLight* SmartLight_Create(void) {
    SmartLight* me = (SmartLight*)malloc(sizeof(SmartLight));
    if (me != NULL) {
        SmartLight_Init(me);
    }
    return me;
}

void SmartLight_Destroy(SmartLight* const me) {
    if (me != NULL) {
        SmartLight_Cleanup(me);
        free(me);
    }
}

// Basic operations
void SmartLight_turnOn(SmartLight* const me) {
    if (me == NULL || me->light == NULL) return;
    
    Light_turnOn(me->light);
    
    // Apply current brightness and settings
    Light_setColor(me->light, (me->energy_saving) ? GREEN : RED);
    
    // Reset auto-off timer if in timer mode
    if (me->mode == TIMER_MODE && me->auto_timer) {
        Timer_setDuration(me->auto_timer, me->auto_timeout);
        Timer_start(me->auto_timer);
    }
    
    printf("SmartLight turned ON (%s mode, %s brightness)\n", 
           modeToString(me->mode), brightnessToString(me->brightness));
}

void SmartLight_turnOff(SmartLight* const me) {
    if (me == NULL || me->light == NULL) return;
    
    Light_turnOff(me->light);
    
    // Stop timers
    if (me->auto_timer) Timer_stop(me->auto_timer);
    if (me->fade_timer) Timer_stop(me->fade_timer);
    
    printf("SmartLight turned OFF\n");
}

void SmartLight_toggle(SmartLight* const me) {
    if (me == NULL || me->light == NULL) return;
    
    if (Light_isOn(me->light)) {
        SmartLight_turnOff(me);
    } else {
        SmartLight_turnOn(me);
    }
}

// AND Pattern operations - these can be changed independently
void SmartLight_setMode(SmartLight* const me, SmartMode mode) {
    if (me == NULL) return;
    
    me->mode = mode;
    printf("SmartLight mode changed to: %s\n", modeToString(mode));
    
    // Adjust behavior based on mode
    switch (mode) {
        case MANUAL_MODE:
            if (me->auto_timer) Timer_stop(me->auto_timer);
            break;
            
        case AUTO_MODE:
            // Enable sensors
            if (me->light_sensor) Sensor_setPowerMode(me->light_sensor, POWER_NORMAL);
            if (me->motion_sensor) Sensor_setPowerMode(me->motion_sensor, POWER_NORMAL);
            break;
            
        case TIMER_MODE:
            if (me->auto_timer && Light_isOn(me->light)) {
                Timer_setDuration(me->auto_timer, me->auto_timeout);
                Timer_start(me->auto_timer);
            }
            break;
            
        case ADAPTIVE_MODE:
            // Start learning from user behavior
            SmartLight_learnFromUsage(me);
            break;
    }
}

void SmartLight_setBrightness(SmartLight* const me, BrightnessLevel level) {
    if (me == NULL || me->light == NULL) return;
    
    me->brightness = level;
    
    // Map brightness to color intensity (simplified)
    ColorType color = RED;  // Default
    switch (level) {
        case BRIGHTNESS_OFF:
            Light_turnOff(me->light);
            return;
        case BRIGHTNESS_DIM:
            color = GREEN;
            break;
        case BRIGHTNESS_MEDIUM:
            color = YELLOW;
            break;
        case BRIGHTNESS_BRIGHT:
        case BRIGHTNESS_MAX:
            color = RED;
            break;
    }
    
    if (Light_isOn(me->light)) {
        Light_setColor(me->light, color);
    }
    
    printf("SmartLight brightness set to: %s\n", brightnessToString(level));
}

void SmartLight_setColor(SmartLight* const me, ColorType color) {
    if (me == NULL || me->light == NULL) return;
    
    Light_setColor(me->light, color);
    me->manual_overrides++;  // Count manual interventions
    
    printf("SmartLight color changed (manual override #%d)\n", me->manual_overrides);
}

void SmartLight_setFlashMode(SmartLight* const me, FlashType mode) {
    if (me == NULL || me->light == NULL) return;
    
    Light_setMode(me->light, mode);
    me->manual_overrides++;
    
    printf("SmartLight flash mode changed (manual override #%d)\n", me->manual_overrides);
}

// Feature control
void SmartLight_enableMotionDetection(SmartLight* const me, bool enable) {
    if (me == NULL) return;
    
    me->motion_enabled = enable;
    
    if (me->motion_sensor) {
        PowerMode power = enable ? POWER_NORMAL : POWER_SLEEP;
        Sensor_setPowerMode(me->motion_sensor, power);
    }
    
    printf("Motion detection: %s\n", enable ? "ENABLED" : "DISABLED");
}

void SmartLight_enableAutoDimming(SmartLight* const me, bool enable) {
    if (me == NULL) return;
    
    me->auto_dimming = enable;
    printf("Auto-dimming: %s\n", enable ? "ENABLED" : "DISABLED");
}

void SmartLight_enableEnergySaving(SmartLight* const me, bool enable) {
    if (me == NULL) return;
    
    me->energy_saving = enable;
    
    // Adjust sensor power modes for energy saving
    if (me->light_sensor && me->motion_sensor) {
        PowerMode power = enable ? POWER_LOW : POWER_NORMAL;
        Sensor_setPowerMode(me->light_sensor, power);
        Sensor_setPowerMode(me->motion_sensor, power);
    }
    
    printf("Energy saving: %s\n", enable ? "ENABLED" : "DISABLED");
}

// Configuration
void SmartLight_setLightThreshold(SmartLight* const me, float threshold) {
    if (me == NULL) return;
    
    me->light_threshold = threshold;
    printf("Light threshold set to: %.1f lux\n", (double)threshold);
}

void SmartLight_setFadeDuration(SmartLight* const me, unsigned int duration_ms) {
    if (me == NULL) return;
    
    me->fade_duration = duration_ms;
    if (me->fade_timer) {
        Timer_setDuration(me->fade_timer, duration_ms);
    }
    
    printf("Fade duration set to: %d ms\n", duration_ms);
}

void SmartLight_setAutoTimeout(SmartLight* const me, unsigned int timeout_ms) {
    if (me == NULL) return;
    
    me->auto_timeout = timeout_ms;
    if (me->auto_timer) {
        Timer_setDuration(me->auto_timer, timeout_ms);
    }
    
    printf("Auto timeout set to: %d ms\n", timeout_ms);
}

// Smart operations
void SmartLight_update(SmartLight* const me) {
    if (me == NULL) return;
    
    // Update all timers
    if (me->auto_timer) Timer_update(me->auto_timer);
    if (me->fade_timer) Timer_update(me->fade_timer);
    
    // Take sensor readings
    if (me->light_sensor && Sensor_isReady(me->light_sensor)) {
        Sensor_takeSample(me->light_sensor);
    }
    if (me->motion_sensor && Sensor_isReady(me->motion_sensor)) {
        Sensor_takeSample(me->motion_sensor);
    }
    
    // Handle mode-specific behavior
    switch (me->mode) {
        case AUTO_MODE:
            SmartLight_adjustToAmbientLight(me);
            if (me->motion_enabled) {
                SmartLight_respondToMotion(me);
            }
            break;
            
        case TIMER_MODE:
            if (me->auto_timer && Timer_isExpired(me->auto_timer)) {
                printf("Auto-off timer expired\n");
                SmartLight_turnOff(me);
            }
            break;
            
        case ADAPTIVE_MODE:
            // Implement learning behavior
            SmartLight_adjustToAmbientLight(me);
            SmartLight_respondToMotion(me);
            break;
            
        case MANUAL_MODE:
            // No automatic behavior
            break;
    }
}

void SmartLight_fadeToLevel(SmartLight* const me, BrightnessLevel target) {
    if (me == NULL) return;
    
    printf("Fading from %s to %s brightness\n",
           brightnessToString(me->brightness),
           brightnessToString(target));
    
    // Start fade timer
    if (me->fade_timer) {
        Timer_start(me->fade_timer);
    }
    
    // For simplicity, just set the target immediately
    // In a real implementation, this would gradually change
    SmartLight_setBrightness(me, target);
}

void SmartLight_respondToMotion(SmartLight* const me) {
    if (me == NULL || !me->motion_enabled || me->motion_sensor == NULL) return;
    
    // Simulate motion detection (value > 0.5 means motion)
    float motion_value = Sensor_getValue(me->motion_sensor);
    bool motion_detected = motion_value > 0.5f;
    
    if (motion_detected != me->last_motion_state) {
        me->last_motion_state = motion_detected;
        
        if (motion_detected) {
            printf("Motion detected! ");
            if (!Light_isOn(me->light)) {
                SmartLight_turnOn(me);
            } else {
                // Increase brightness on motion
                if (me->brightness < BRIGHTNESS_BRIGHT) {
                    SmartLight_fadeToLevel(me, me->brightness + 1);
                }
            }
        } else {
            printf("Motion stopped. ");
            if (me->mode == AUTO_MODE && me->auto_timer) {
                Timer_start(me->auto_timer);  // Start auto-off countdown
            }
        }
    }
}

void SmartLight_adjustToAmbientLight(SmartLight* const me) {
    if (me == NULL || !me->auto_dimming || me->light_sensor == NULL) return;
    
    float ambient_light = Sensor_getValue(me->light_sensor);
    
    // Only adjust if light level changed significantly
    if (abs((int)(ambient_light - me->last_light_level)) > 50) {
        me->last_light_level = ambient_light;
        
        if (ambient_light < me->light_threshold) {
            // Dark environment - turn on or increase brightness
            if (!Light_isOn(me->light)) {
                SmartLight_turnOn(me);
            } else if (me->brightness < BRIGHTNESS_MEDIUM) {
                SmartLight_fadeToLevel(me, BRIGHTNESS_MEDIUM);
            }
            printf("Low ambient light (%.1f lux) - adjusting brightness\n", (double)ambient_light);
        } else {
            // Bright environment - dim or turn off
            if (Light_isOn(me->light) && me->brightness > BRIGHTNESS_DIM) {
                SmartLight_fadeToLevel(me, BRIGHTNESS_DIM);
                printf("High ambient light (%.1f lux) - dimming\n", (double)ambient_light);
            }
        }
    }
}

// Status and information
void SmartLight_displayStatus(SmartLight* const me) {
    if (me == NULL) {
        printf("SmartLight: NULL pointer\n");
        return;
    }
    
    printf("=== SmartLight Status ===\n");
    printf("Mode: %s | Brightness: %s | On: %s\n",
           modeToString(me->mode),
           brightnessToString(me->brightness),
           (Light_isOn(me->light)) ? "YES" : "NO");
    
    printf("Features: Motion=%s, AutoDim=%s, EnergySave=%s\n",
           me->motion_enabled ? "ON" : "OFF",
           me->auto_dimming ? "ON" : "OFF",
           me->energy_saving ? "ON" : "OFF");
    
    printf("Manual overrides: %d\n", me->manual_overrides);
    
    // Show component status
    if (me->light) {
        printf("Light: ");
        Light_displayStatus(me->light);
    }
    
    if (me->light_sensor) {
        printf("Ambient light sensor: ");
        Sensor_displayStatus(me->light_sensor);
    }
    
    if (me->motion_sensor) {
        printf("Motion sensor: ");
        Sensor_displayStatus(me->motion_sensor);
    }
    
    printf("========================\n");
}

bool SmartLight_isOn(SmartLight* const me) {
    return (me != NULL && me->light != NULL) ? Light_isOn(me->light) : false;
}

SmartMode SmartLight_getMode(SmartLight* const me) {
    return (me != NULL) ? me->mode : MANUAL_MODE;
}

BrightnessLevel SmartLight_getBrightness(SmartLight* const me) {
    return (me != NULL) ? me->brightness : BRIGHTNESS_OFF;
}

// Statistics and learning
unsigned int SmartLight_getManualOverrides(SmartLight* const me) {
    return (me != NULL) ? me->manual_overrides : 0;
}

void SmartLight_resetStatistics(SmartLight* const me) {
    if (me == NULL) return;
    
    me->manual_overrides = 0;
    
    if (me->light_sensor) Sensor_resetStatistics(me->light_sensor);
    if (me->motion_sensor) Sensor_resetStatistics(me->motion_sensor);
    
    printf("SmartLight statistics reset\n");
}

void SmartLight_learnFromUsage(SmartLight* const me) {
    if (me == NULL) return;
    
    // Simple learning: adjust thresholds based on manual overrides
    if (me->manual_overrides > 10) {
        // User frequently overrides - maybe adjust sensitivity
        me->light_threshold *= 0.9f;  // Make more sensitive
        printf("Learning: Adjusted light sensitivity based on usage patterns\n");
    }
}

// String conversion helpers
const char* SmartLight_getModeString(SmartLight* const me) {
    return (me != NULL) ? modeToString(me->mode) : "NULL";
}

const char* SmartLight_getBrightnessString(SmartLight* const me) {
    return (me != NULL) ? brightnessToString(me->brightness) : "NULL";
}
