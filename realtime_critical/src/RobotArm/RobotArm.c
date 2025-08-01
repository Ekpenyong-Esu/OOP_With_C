#include "RobotArm.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Default safety limits
#define DEFAULT_MIN_X -1000.0f
#define DEFAULT_MAX_X 1000.0f
#define DEFAULT_MIN_Y -1000.0f
#define DEFAULT_MAX_Y 1000.0f
#define DEFAULT_MIN_Z 0.0f
#define DEFAULT_MAX_Z 1000.0f
#define DEFAULT_MAX_VELOCITY 500.0f
#define DEFAULT_MAX_ACCELERATION 250.0f

// Helper functions
static bool isPositionInLimits(const RobotArm* me, float x, float y, float z) {
    float distance = sqrt(x*x + y*y); // Explicit use of sqrt from math.h
    float maxRadius = (me->limits.maxX - me->limits.minX) / 2.0f;
    
    return (distance <= maxRadius &&
            x >= me->limits.minX && x <= me->limits.maxX &&
            y >= me->limits.minY && y <= me->limits.maxY &&
            z >= me->limits.minZ && z <= me->limits.maxZ);
}

static void setDefaultLimits(ArmLimits* limits) {
    limits->minX = DEFAULT_MIN_X;
    limits->maxX = DEFAULT_MAX_X;
    limits->minY = DEFAULT_MIN_Y;
    limits->maxY = DEFAULT_MAX_Y;
    limits->minZ = DEFAULT_MIN_Z;
    limits->maxZ = DEFAULT_MAX_Z;
    limits->maxVelocity = DEFAULT_MAX_VELOCITY;
    limits->maxAcceleration = DEFAULT_MAX_ACCELERATION;
}

// Lifecycle Management implementations
RobotArm* RobotArm_Create(void) {
    RobotArm* me = (RobotArm*)malloc(sizeof(RobotArm));
    if (me != NULL) {
        me->isInitialized = false;
        me->status = MOTION_STATUS_ERROR;
        me->currentX = me->currentY = me->currentZ = 0.0f;
        me->targetX = me->targetY = me->targetZ = 0.0f;
        me->currentVelocity = me->currentAcceleration = 0.0f;
        setDefaultLimits(&me->limits);
        me->errorCount = 0;
    }
    return me;
}

void RobotArm_Destroy(RobotArm* const me) {
    if (me != NULL) {
        RobotArm_Cleanup(me);
        free(me);
    }
}

bool RobotArm_Init(RobotArm* const me) {
    if (!me) return false;
    
    me->isInitialized = true;
    me->status = MOTION_STATUS_OK;
    me->currentX = me->currentY = me->currentZ = 0.0f;
    me->targetX = me->targetY = me->targetZ = 0.0f;
    me->currentVelocity = me->currentAcceleration = 0.0f;
    setDefaultLimits(&me->limits);
    me->errorCount = 0;
    
    return true;
}

void RobotArm_Cleanup(RobotArm* const me) {
    if (!me) return;
    
    // Ensure arm is in safe position before cleanup
    RobotArm_emergencyStop(me);
    me->isInitialized = false;
    me->status = MOTION_STATUS_ERROR;
}

// Motion Control implementations
bool RobotArm_moveTo(RobotArm* const me, float x, float y, float z) {
    if (!me || !me->isInitialized) {
        return false;
    }
    
    // Validate target position
    if (!isPositionInLimits(me, x, y, z)) {
        me->errorCount++;
        me->status = MOTION_STATUS_LIMIT_REACHED;
        return false;
    }
    
    // Check if we're already moving
    if (me->status == MOTION_STATUS_BUSY) {
        me->errorCount++;
        return false;
    }
    
    me->targetX = x;
    me->targetY = y;
    me->targetZ = z;
    me->status = MOTION_STATUS_BUSY;
    
    // In a real implementation, this would trigger actual motor movement
    // For simulation, we'll just update the current position
    me->currentX = x;
    me->currentY = y;
    me->currentZ = z;
    me->status = MOTION_STATUS_OK;
    
    return true;
}

bool RobotArm_moveRelative(RobotArm* const me, float dx, float dy, float dz) {
    if (!me || !me->isInitialized) {
        return false;
    }
    
    return RobotArm_moveTo(me, 
                          me->currentX + dx,
                          me->currentY + dy,
                          me->currentZ + dz);
}

bool RobotArm_stop(RobotArm* const me) {
    if (!me || !me->isInitialized) {
        return false;
    }
    
    // Gradual stop - update targets to current position
    me->targetX = me->currentX;
    me->targetY = me->currentY;
    me->targetZ = me->currentZ;
    me->currentVelocity = 0.0f;
    me->currentAcceleration = 0.0f;
    me->status = MOTION_STATUS_OK;
    
    return true;
}

bool RobotArm_emergencyStop(RobotArm* const me) {
    if (!me) {
        return false;
    }
    
    // Immediate stop - no gradual deceleration
    me->targetX = me->currentX;
    me->targetY = me->currentY;
    me->targetZ = me->currentZ;
    me->currentVelocity = 0.0f;
    me->currentAcceleration = 0.0f;
    me->status = MOTION_STATUS_EMERGENCY_STOP;
    me->errorCount++;
    
    return true;
}

bool RobotArm_resetPosition(RobotArm* const me) {
    if (!me || !me->isInitialized) {
        return false;
    }
    
    return RobotArm_moveTo(me, 0.0f, 0.0f, 0.0f);
}

// Configuration implementations
bool RobotArm_setLimits(RobotArm* const me, const ArmLimits* limits) {
    if (!me || !limits) {
        return false;
    }
    
    // Validate new limits
    if (limits->minX >= limits->maxX ||
        limits->minY >= limits->maxY ||
        limits->minZ >= limits->maxZ ||
        limits->maxVelocity <= 0.0f ||
        limits->maxAcceleration <= 0.0f) {
        me->errorCount++;
        return false;
    }
    
    memcpy(&me->limits, limits, sizeof(ArmLimits));
    return true;
}

bool RobotArm_getLimits(const RobotArm* const me, ArmLimits* limits) {
    if (!me || !limits) {
        return false;
    }
    
    memcpy(limits, &me->limits, sizeof(ArmLimits));
    return true;
}

bool RobotArm_setMaxVelocity(RobotArm* const me, float velocity) {
    if (!me || velocity <= 0.0f) {
        return false;
    }
    
    me->limits.maxVelocity = velocity;
    return true;
}

bool RobotArm_setMaxAcceleration(RobotArm* const me, float acceleration) {
    if (!me || acceleration <= 0.0f) {
        return false;
    }
    
    me->limits.maxAcceleration = acceleration;
    return true;
}

// Status and Diagnostics implementations
bool RobotArm_isInitialized(const RobotArm* const me) {
    return me ? me->isInitialized : false;
}

MotionStatus RobotArm_getStatus(const RobotArm* const me) {
    return me ? me->status : MOTION_STATUS_ERROR;
}

bool RobotArm_getCurrentPosition(const RobotArm* const me, float* x, float* y, float* z) {
    if (!me || !x || !y || !z) {
        return false;
    }
    
    *x = me->currentX;
    *y = me->currentY;
    *z = me->currentZ;
    return true;
}

bool RobotArm_getTargetPosition(const RobotArm* const me, float* x, float* y, float* z) {
    if (!me || !x || !y || !z) {
        return false;
    }
    
    *x = me->targetX;
    *y = me->targetY;
    *z = me->targetZ;
    return true;
}

uint32_t RobotArm_getErrorCount(const RobotArm* const me) {
    return me ? me->errorCount : 0;
}