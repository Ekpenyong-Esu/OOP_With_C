#ifndef SAFETYMONITOR_H
#define SAFETYMONITOR_H

#include <stdbool.h>
#include <stdint.h>

// Forward declarations
typedef struct SafetyMonitor SafetyMonitor;

// Simple diagnostic levels
typedef enum {
    DIAG_INFO,
    DIAG_WARNING,
    DIAG_ERROR,
    DIAG_CRITICAL
} DiagnosticLevel;

// Basic safety monitor structure
struct SafetyMonitor {
    bool isActive;
    bool emergencyStopActive;
    uint32_t errorCount;
    DiagnosticLevel currentLevel;
};

// Core functions
SafetyMonitor* SafetyMonitor_Create(void);
void SafetyMonitor_Destroy(SafetyMonitor* me);

bool SafetyMonitor_EmergencyStop(SafetyMonitor* me);
bool SafetyMonitor_Reset(SafetyMonitor* me);
bool SafetyMonitor_LogError(SafetyMonitor* me, const char* message, DiagnosticLevel level);

#endif // SAFETYMONITOR_H