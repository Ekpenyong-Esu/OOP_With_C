#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

static const char * const project_name = "CTemplate";
static const char * const project_version = "1.0.0";
static const int32_t project_version_major =  1;
static const int32_t project_version_minor = 0;
static const int32_t project_version_patch = 0;
static const char * const git_sha = "";

// Safety-Critical Configuration
#define SAFETY_VERSION_MAJOR 1
#define SAFETY_VERSION_MINOR 0
#define SAFETY_VERSION_PATCH 0

// Real-time Configuration
#define RT_PRIORITY_HIGH 99
#define RT_PRIORITY_MEDIUM 80
#define RT_PRIORITY_LOW 60

// Safety Timeouts (in milliseconds)
#define CRITICAL_OPERATION_TIMEOUT 100
#define EMERGENCY_STOP_TIMEOUT 50
#define WATCHDOG_TIMEOUT 500

// Memory Safety
#define MAX_STACK_SIZE (16 * 1024)  // 16KB stack size
#define MAX_HEAP_ALLOCATION (32 * 1024)  // 32KB max heap allocation

// Error Management
#define MAX_ERROR_RETRIES 3
#define ERROR_LOG_SIZE 1024

// Diagnostic Levels
typedef enum {
    DIAG_NONE = 0,
    DIAG_ERROR = 1,
    DIAG_WARNING = 2,
    DIAG_INFO = 3,
    DIAG_DEBUG = 4
} DiagnosticLevel;

// System States
typedef enum {
    SYS_INIT,
    SYS_READY,
    SYS_RUNNING,
    SYS_ERROR,
    SYS_EMERGENCY_STOP,
    SYS_MAINTENANCE
} SystemState;

#endif // CONFIG_H
