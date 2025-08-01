#include "UserInput.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stddef.h>

#define MAX_COMMAND_LENGTH 128
#define POSITION_TOLERANCE 0.001f

// Helper functions
static bool parseFloatValue(const char* str, float* value) {
    char* endptr;
    *value = strtof(str, &endptr);
    return endptr != str && *endptr == '\0';
}

static bool isWithinRange(float value, float min, float max) {
    return value >= min && value <= max;
}

// Lifecycle Management implementations
UserInput* UserInput_Create(void) {
    UserInput* me = (UserInput*)malloc(sizeof(UserInput));
    if (me != NULL) {
        UserInput_Init(me);
    }
    return me;
}

void UserInput_Destroy(UserInput* const me) {
    if (me != NULL) {
        UserInput_Cleanup(me);
        free(me);
    }
}

void UserInput_Init(UserInput* const me) {

    me->isInitialized = true;
    me->status = INPUT_VALID;
    me->commandCount = 0;
    me->errorCount = 0;
    me->emergencyStopRequested = false;
}

void UserInput_Cleanup(UserInput* const me) {
    
    me->isInitialized = false;
    me->status = INPUT_ERROR;
}

// Input Processing implementations
InputStatus UserInput_processCommand(UserInput* const me, const char* command) {
    if (!me || !me->isInitialized || !command) {
        return INPUT_ERROR;
    }
    
    me->status = INPUT_VALID;
    
    // Check for emergency stop command
    if (strcasecmp(command, "STOP") == 0 || 
        strcasecmp(command, "EMERGENCY_STOP") == 0) {
        me->emergencyStopRequested = true;
        me->commandCount++;
        return INPUT_VALID;
    }
    
    // Process motion commands in format "MOVE X,Y,Z"
    char cmd[MAX_COMMAND_LENGTH];
    char params[MAX_COMMAND_LENGTH];
    float x, y, z;
    
    if (sscanf(command, "%s %s", cmd, params) == 2) {
        if (strcasecmp(cmd, "MOVE") == 0) {
            char* token = strtok(params, ",");
            if (token && parseFloatValue(token, &x)) {
                token = strtok(NULL, ",");
                if (token && parseFloatValue(token, &y)) {
                    token = strtok(NULL, ",");
                    if (token && parseFloatValue(token, &z)) {
                        // Store parsed values for later retrieval
                        me->lastParsedCommand.x = x;
                        me->lastParsedCommand.y = y;
                        me->lastParsedCommand.z = z;
                        me->lastParsedCommand.useDefaultLimits = true;
                        me->commandCount++;
                        return INPUT_VALID;
                    }
                }
            }
        }
    }
    
    me->errorCount++;
    return INPUT_INVALID_TYPE;
}

InputStatus UserInput_getMotionCommand(UserInput* const me, MotionCommand* cmd) {
    if (!me || !me->isInitialized || !cmd) {
        return INPUT_ERROR;
    }
    
    // In a real implementation, this would get the next motion command from a queue
    // For now, we'll return a simple command
    cmd->x = 0.0f;
    cmd->y = 0.0f;
    cmd->z = 0.0f;
    cmd->maxVelocity = 0.0f;
    cmd->maxAcceleration = 0.0f;
    cmd->useDefaultLimits = true;
    
    return INPUT_VALID;
}

bool UserInput_isEmergencyStopRequested(const UserInput* const me) {
    return me ? me->emergencyStopRequested : false;
}

void UserInput_clearEmergencyStop(UserInput* const me) {
    if (me) {
        me->emergencyStopRequested = false;
    }
}

// Input Validation implementations
InputStatus UserInput_validateMotionCommand(const UserInput* const me, const MotionCommand* cmd) {
    if (!me || !me->isInitialized || !cmd) {
        return INPUT_ERROR;
    }
    
    // Check position ranges
    if (!isWithinRange(cmd->x, -1000.0f, 1000.0f) ||
        !isWithinRange(cmd->y, -1000.0f, 1000.0f) ||
        !isWithinRange(cmd->z, 0.0f, 1000.0f)) {
        return INPUT_INVALID_RANGE;
    }
    
    // If custom limits are specified, validate them
    if (!cmd->useDefaultLimits) {
        if (cmd->maxVelocity <= 0.0f || cmd->maxVelocity > 1000.0f ||
            cmd->maxAcceleration <= 0.0f || cmd->maxAcceleration > 500.0f) {
            return INPUT_INVALID_RANGE;
        }
    }
    
    return INPUT_VALID;
}

InputStatus UserInput_validateConfiguration(const UserInput* const me, const void* config, size_t configSize) {
    if (!me || !me->isInitialized || !config || configSize == 0) {
        return INPUT_ERROR;
    }
    
    // In a real implementation, this would validate configuration parameters
    // For now, just return valid
    return INPUT_VALID;
}

// Status and Diagnostics implementations
bool UserInput_isInitialized(const UserInput* const me) {
    return me ? me->isInitialized : false;
}

InputStatus UserInput_getStatus(const UserInput* const me) {
    return me ? me->status : INPUT_ERROR;
}

uint32_t UserInput_getCommandCount(const UserInput* const me) {
    return me ? me->commandCount : 0;
}

uint32_t UserInput_getErrorCount(const UserInput* const me) {
    return me ? me->errorCount : 0;
}