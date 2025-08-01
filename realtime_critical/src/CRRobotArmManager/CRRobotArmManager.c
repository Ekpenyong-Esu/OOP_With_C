//
// Created by mahon on 1/25/2024.
//

#include "CRRobotArmManager.h"
#include "SafetyMonitor.h"
#include "RobotArm.h"
#include "CRDisplay.h"
#include <stdlib.h>
#include <math.h>

// Safety limits
#define MAX_VELOCITY 1000.0f
#define SAFE_ZONE_MARGIN 50.0f
#define WORKSPACE_LIMIT 1000.0f
#define MAX_HEIGHT 800.0f

// Helper function for position validation
static bool isPositionSafe(Position3D pos) {
    float distance = sqrt(pos.x * pos.x + pos.y * pos.y);
    return (distance <= WORKSPACE_LIMIT &&
            pos.z >= 0 && 
            pos.z <= MAX_HEIGHT);
}

// Core Functions Implementation
CRRobotArmManager* CRRobotArmManager_Create(struct SafetyMonitor* safety) {
    if (!safety) return NULL;

    CRRobotArmManager* me = (CRRobotArmManager*)malloc(sizeof(CRRobotArmManager));
    if (me) {
        me->safety = safety;
        me->arm = NULL;
        me->display = NULL;
        me->currentPosition = (Position3D){0, 0, 0};
        me->targetPosition = (Position3D){0, 0, 0};
        me->state = MOTION_IDLE;
        me->isInitialized = false;
        me->currentVelocity = 0;
    }
    return me;
}

void CRRobotArmManager_Destroy(CRRobotArmManager* me) {
    if (!me) return;

    // Ensure safe shutdown
    if (me->state == MOTION_MOVING) {
        CRRobotArmManager_EmergencyStop(me);
    }
    free(me);
}

// Motion Control Implementation
bool CRRobotArmManager_MoveTo(CRRobotArmManager* me, Position3D target) {
    if (!me || !me->isInitialized) return false;

    taskENTER_CRITICAL();  // Enter critical section for state check and update

    // Safety checks
    if (me->state != MOTION_IDLE || !isPositionSafe(target)) {
        if (me->display) {
            CRDisplay_printMsg(me->display, "Invalid motion request");
        }
        taskEXIT_CRITICAL();
        return false;
    }

    // Update state and target
    me->targetPosition = target;
    me->state = MOTION_MOVING;

    // Command the hardware
    bool success = RobotArm_moveTo(me->arm, target.x, target.y, target.z);
    
    if (!success) {
        me->state = MOTION_ERROR;
        if (me->display) {
            CRDisplay_printMsg(me->display, "Motion command failed");
        }
    }

    taskEXIT_CRITICAL();
    return success;
}

bool CRRobotArmManager_Stop(CRRobotArmManager* me) {
    if (!me || !me->isInitialized) return false;

    taskENTER_CRITICAL();
    
    bool success = RobotArm_stop(me->arm);
    if (success) {
        me->state = MOTION_IDLE;
    }
    
    taskEXIT_CRITICAL();
    return success;
}

bool CRRobotArmManager_EmergencyStop(CRRobotArmManager* me) {
    if (!me) return false;

    taskENTER_CRITICAL();
    
    // Emergency stop should work even if not fully initialized
    if (me->arm) {
        RobotArm_emergencyStop(me->arm);
    }
    me->state = MOTION_ERROR;
    me->currentVelocity = 0;
    
    if (me->safety) {
        SafetyMonitor_EmergencyStop(me->safety);
    }
    
    if (me->display) {
        CRDisplay_printMsg(me->display, "EMERGENCY STOP ACTIVATED");
    }
    
    taskEXIT_CRITICAL();
    return true;
}

// Safety and Status Implementation
bool CRRobotArmManager_IsInSafeZone(const CRRobotArmManager* me) {
    if (!me) return false;

    Position3D pos = me->currentPosition;
    float margin = SAFE_ZONE_MARGIN;
    
    return (fabs(pos.x) <= (WORKSPACE_LIMIT - margin) &&
            fabs(pos.y) <= (WORKSPACE_LIMIT - margin) &&
            pos.z >= margin &&
            pos.z <= (MAX_HEIGHT - margin));
}

MotionState CRRobotArmManager_GetState(const CRRobotArmManager* me) {
    return me ? me->state : MOTION_ERROR;
}

Position3D CRRobotArmManager_GetPosition(const CRRobotArmManager* me) {
    return me ? me->currentPosition : (Position3D){0, 0, 0};
}

// Component Setup Implementation
bool CRRobotArmManager_SetDisplay(CRRobotArmManager* me, struct CRDisplay* display) {
    if (!me || !display) return false;
    me->display = display;
    return true;
}

bool CRRobotArmManager_SetRobotArm(CRRobotArmManager* me, struct RobotArm* arm) {
    if (!me || !arm) return false;
    me->arm = arm;
    me->isInitialized = (me->arm != NULL && me->safety != NULL);
    return true;
}