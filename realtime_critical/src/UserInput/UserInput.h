#ifndef USERINPUT_H
#define USERINPUT_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Forward declarations
typedef struct UserInput UserInput;

// Input types
typedef enum {
    INPUT_MOTION_COMMAND,
    INPUT_EMERGENCY_STOP,
    INPUT_CONFIGURATION,
    INPUT_CALIBRATION,
    INPUT_DIAGNOSTIC
} InputType;

// Input validation status
typedef enum {
    INPUT_VALID,
    INPUT_INVALID_RANGE,
    INPUT_INVALID_TYPE,
    INPUT_INVALID_STATE,
    INPUT_ERROR
} InputStatus;

// Motion command input
typedef struct {
    float x, y, z;           // Target position
    float maxVelocity;       // Optional velocity limit
    float maxAcceleration;   // Optional acceleration limit
    bool useDefaultLimits;   // Whether to use system defaults
} MotionCommand;

struct UserInput {
    bool isInitialized;
    InputStatus status;
    uint32_t commandCount;
    uint32_t errorCount;
    bool emergencyStopRequested;
    MotionCommand lastParsedCommand;  // Store last parsed motion command
};

// Lifecycle Management
UserInput* UserInput_Create(void);
void UserInput_Destroy(UserInput* const me);
void UserInput_Init(UserInput* const me);
void UserInput_Cleanup(UserInput* const me);

// Input Processing
InputStatus UserInput_processCommand(UserInput* const me, const char* command);
InputStatus UserInput_getMotionCommand(UserInput* const me, MotionCommand* cmd);
bool UserInput_isEmergencyStopRequested(const UserInput* const me);
void UserInput_clearEmergencyStop(UserInput* const me);

// Input Validation
InputStatus UserInput_validateMotionCommand(const UserInput* const me, const MotionCommand* cmd);
InputStatus UserInput_validateConfiguration(const UserInput* const me, const void* config, size_t configSize);

// Status and Diagnostics
bool UserInput_isInitialized(const UserInput* const me);
InputStatus UserInput_getStatus(const UserInput* const me);
uint32_t UserInput_getCommandCount(const UserInput* const me);
uint32_t UserInput_getErrorCount(const UserInput* const me);

#endif // USERINPUT_H