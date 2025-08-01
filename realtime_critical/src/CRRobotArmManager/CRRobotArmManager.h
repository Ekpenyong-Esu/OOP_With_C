#ifndef CRROBOTARMMANAGER_H
#define CRROBOTARMMANAGER_H

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

// Forward declarations
struct SafetyMonitor;
struct RobotArm;
struct CRDisplay;

// Simple 3D position structure
typedef struct {
    float x, y, z;
} Position3D;

// Basic motion states
typedef enum {
    MOTION_IDLE,
    MOTION_MOVING,
    MOTION_ERROR
} MotionState;

// Main manager structure
typedef struct {
    // Hardware interfaces
    struct RobotArm* arm;
    struct SafetyMonitor* safety;
    struct CRDisplay* display;
    
    // State
    Position3D currentPosition;
    Position3D targetPosition;
    MotionState state;
    bool isInitialized;
    float currentVelocity;
} CRRobotArmManager;

// Core Functions
CRRobotArmManager* CRRobotArmManager_Create(struct SafetyMonitor* safety);
void CRRobotArmManager_Destroy(CRRobotArmManager* me);

// Motion Control
bool CRRobotArmManager_MoveTo(CRRobotArmManager* me, Position3D target);
bool CRRobotArmManager_Stop(CRRobotArmManager* me);
bool CRRobotArmManager_EmergencyStop(CRRobotArmManager* me);

// Safety and Status
bool CRRobotArmManager_IsInSafeZone(const CRRobotArmManager* me);
MotionState CRRobotArmManager_GetState(const CRRobotArmManager* me);
Position3D CRRobotArmManager_GetPosition(const CRRobotArmManager* me);

// Component Setup
bool CRRobotArmManager_SetDisplay(CRRobotArmManager* me, struct CRDisplay* display);
bool CRRobotArmManager_SetRobotArm(CRRobotArmManager* me, struct RobotArm* arm);

#endif // CRROBOTARMMANAGER_H
