#include "SafetyMonitor.h"
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

static BaseType_t enterCriticalRegionWithTimeout(void) {
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(CRITICAL_OPERATION_TIMEOUT);
    return xTaskNotifyWait(0, 0, NULL, xMaxBlockTime);
}

SafetyMonitor* SafetyMonitor_Create(void) {
    SafetyMonitor* me = (SafetyMonitor*)malloc(sizeof(SafetyMonitor));
    if (me != NULL) {
        SafetyMonitor_Init(me);
    }
    return me;
}

void SafetyMonitor_Init(SafetyMonitor* const me) {
    if (!me) return;
    
    me->currentState = SYS_INIT;
    me->watchdogTimer = 0;
    me->errorCount = 0;
    me->emergencyStopActive = false;
    me->diagLevel = DIAG_INFO;
}

void SafetyMonitor_Destroy(SafetyMonitor* const me) {
    if (!me) return;
    
    // Ensure safe shutdown
    if (me->currentState != SYS_INIT) {
        SafetyMonitor_EmergencyStop(me);
    }
    free(me);
}

bool SafetyMonitor_CheckState(SafetyMonitor* const me) {
    if (!me) return false;

    if (enterCriticalRegionWithTimeout() != pdTRUE) {
        me->errorCount++;
        return false;
    }

    taskENTER_CRITICAL();
    
    bool isHealthy = (me->watchdogTimer < WATCHDOG_TIMEOUT) &&
                    (me->errorCount < MAX_ERROR_RETRIES) &&
                    !me->emergencyStopActive;
    
    taskEXIT_CRITICAL();
    
    return isHealthy;
}

bool SafetyMonitor_EmergencyStop(SafetyMonitor* const me) {
    if (!me) return false;

    taskENTER_CRITICAL();
    
    me->emergencyStopActive = true;
    me->currentState = SYS_EMERGENCY_STOP;
    
    // Additional emergency procedures would go here
    
    taskEXIT_CRITICAL();
    
    return true;
}

bool SafetyMonitor_ResetWatchdog(SafetyMonitor* const me) {
    if (!me) return false;

    taskENTER_CRITICAL();
    me->watchdogTimer = 0;
    taskEXIT_CRITICAL();
    
    return true;
}

bool SafetyMonitor_LogError(SafetyMonitor* const me, const char* message, DiagnosticLevel level) {
    if (!me || !message) return false;

    taskENTER_CRITICAL();
    
    if (level <= me->diagLevel) {
        me->errorCount++;
        // Implement actual error logging here
        if (me->errorCount >= MAX_ERROR_RETRIES) {
            SafetyMonitor_EmergencyStop(me);
        }
    }
    
    taskEXIT_CRITICAL();
    
    return true;
}

SystemState SafetyMonitor_GetState(const SafetyMonitor* const me) {
    return me ? me->currentState : SYS_ERROR;
}

bool SafetyMonitor_SetState(SafetyMonitor* const me, SystemState newState) {
    if (!me) return false;

    taskENTER_CRITICAL();
    
    // Validate state transitions
    bool validTransition = true;
    switch (me->currentState) {
        case SYS_INIT:
            validTransition = (newState == SYS_READY);
            break;
        case SYS_READY:
            validTransition = (newState == SYS_RUNNING || newState == SYS_ERROR);
            break;
        case SYS_RUNNING:
            validTransition = (newState == SYS_ERROR || newState == SYS_EMERGENCY_STOP || 
                             newState == SYS_MAINTENANCE);
            break;
        default:
            validTransition = (newState == SYS_INIT);
            break;
    }

    if (validTransition) {
        me->currentState = newState;
    }
    
    taskEXIT_CRITICAL();
    
    return validTransition;
}

bool SafetyMonitor_IsEmergencyStopActive(const SafetyMonitor* const me) {
    return me ? me->emergencyStopActive : true;
}