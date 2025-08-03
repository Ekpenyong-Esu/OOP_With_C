//
// SmartLight Component - Advanced AND Pattern Demonstration
// This combines multiple components to show complex AND patterns:
// - Light state (from Light component)
// - Timer-based behavior (from Timer component)  
// - Sensor-driven responses (from Sensor component)
//

#ifndef ANDSTATE_SMARTLIGHT_H
#define ANDSTATE_SMARTLIGHT_H

#include "../Light/Light.h"
#include "../Timer/Timer.h"
#include "../Sensor/Sensor.h"
#include <stdbool.h>

typedef enum SmartMode {
    MANUAL_MODE,        // User controls everything
    AUTO_MODE,          // Responds to sensors
    TIMER_MODE,         // Timer-based operation
    ADAPTIVE_MODE       // Learns and adapts
} SmartMode;

typedef enum BrightnessLevel {
    BRIGHTNESS_OFF,
    BRIGHTNESS_DIM,
    BRIGHTNESS_MEDIUM,
    BRIGHTNESS_BRIGHT,
    BRIGHTNESS_MAX
} BrightnessLevel;

typedef struct SmartLight SmartLight;
struct SmartLight {
    // Component composition - multiple AND aspects
    Light* light;               // Basic light functionality
    Timer* auto_timer;          // Automatic timing
    Timer* fade_timer;          // Smooth transitions
    Sensor* light_sensor;       // Ambient light detection
    Sensor* motion_sensor;      // Motion detection
    
    // SmartLight specific AND aspects
    SmartMode mode;             // Operating mode
    BrightnessLevel brightness; // Brightness level
    bool motion_enabled;        // Motion detection active
    bool auto_dimming;          // Automatic brightness adjustment
    bool energy_saving;         // Energy saving mode
    
    // Configuration
    float light_threshold;      // Lux level for auto operation
    unsigned int fade_duration; // Fade transition time (ms)
    unsigned int auto_timeout;  // Auto-off timeout (ms)
    
    // State tracking
    bool last_motion_state;     // Previous motion detection
    float last_light_level;     // Previous ambient light
    unsigned int manual_overrides; // Count of manual interventions
};

// Constructor/Destructor
void SmartLight_Init(SmartLight* const me);
void SmartLight_Cleanup(SmartLight* const me);
SmartLight* SmartLight_Create(void);
void SmartLight_Destroy(SmartLight* const me);

// Basic operations
void SmartLight_turnOn(SmartLight* const me);
void SmartLight_turnOff(SmartLight* const me);
void SmartLight_toggle(SmartLight* const me);

// AND Pattern operations - independent aspects
void SmartLight_setMode(SmartLight* const me, SmartMode mode);
void SmartLight_setBrightness(SmartLight* const me, BrightnessLevel level);
void SmartLight_setColor(SmartLight* const me, ColorType color);
void SmartLight_setFlashMode(SmartLight* const me, FlashType mode);

// Feature control - more AND aspects
void SmartLight_enableMotionDetection(SmartLight* const me, bool enable);
void SmartLight_enableAutoDimming(SmartLight* const me, bool enable);
void SmartLight_enableEnergySaving(SmartLight* const me, bool enable);

// Configuration
void SmartLight_setLightThreshold(SmartLight* const me, float threshold);
void SmartLight_setFadeDuration(SmartLight* const me, unsigned int duration_ms);
void SmartLight_setAutoTimeout(SmartLight* const me, unsigned int timeout_ms);

// Smart operations
void SmartLight_update(SmartLight* const me);  // Call regularly for smart behavior
void SmartLight_fadeToLevel(SmartLight* const me, BrightnessLevel target);
void SmartLight_respondToMotion(SmartLight* const me);
void SmartLight_adjustToAmbientLight(SmartLight* const me);

// Status and information
void SmartLight_displayStatus(SmartLight* const me);
bool SmartLight_isOn(SmartLight* const me);
SmartMode SmartLight_getMode(SmartLight* const me);
BrightnessLevel SmartLight_getBrightness(SmartLight* const me);

// Statistics and learning
unsigned int SmartLight_getManualOverrides(SmartLight* const me);
void SmartLight_resetStatistics(SmartLight* const me);
void SmartLight_learnFromUsage(SmartLight* const me);  // Adaptive behavior

// String conversion helpers
const char* SmartLight_getModeString(SmartLight* const me);
const char* SmartLight_getBrightnessString(SmartLight* const me);

#endif //ANDSTATE_SMARTLIGHT_H
