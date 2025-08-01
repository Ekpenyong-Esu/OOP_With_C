#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <stdbool.h>

// Forward declarations
typedef struct RobotArm RobotArm;

// Simple hardware interface structure
struct RobotArm {
    bool isInitialized;
    float currentX, currentY, currentZ;
};

// Basic motor control functions
RobotArm* RobotArm_Create(void);
void RobotArm_Destroy(RobotArm* me);

bool RobotArm_moveTo(RobotArm* me, float x, float y, float z);
bool RobotArm_stop(RobotArm* me);
bool RobotArm_emergencyStop(RobotArm* me);

#endif // ROBOTARM_H