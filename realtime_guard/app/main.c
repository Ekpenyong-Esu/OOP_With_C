#include "SafetyMonitor.h"
#include "RealTimeTaskManager.h"
#include "CRRobotArmManager.h"
#include "CRDisplay.h"
#include "RobotArm.h"
#include "UserInput.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

// Task priorities from highest to lowest
#define SAFETY_TASK_PRIORITY      (configMAX_PRIORITIES - 1)
#define MOTION_TASK_PRIORITY      (configMAX_PRIORITIES - 2)
#define MONITORING_TASK_PRIORITY  (configMAX_PRIORITIES - 3)
#define DIAGNOSTIC_TASK_PRIORITY  (configMAX_PRIORITIES - 4)

// Task stack sizes
#define SAFETY_STACK_SIZE     (2048)
#define MOTION_STACK_SIZE     (2048)
#define MONITOR_STACK_SIZE    (1024)
#define DIAGNOSTIC_STACK_SIZE (1024)

// Task periods in milliseconds
#define SAFETY_TASK_PERIOD    (10)    // 10ms for critical safety checks
#define MOTION_TASK_PERIOD    (20)    // 20ms for motion control
#define MONITOR_TASK_PERIOD   (100)   // 100ms for monitoring
#define DIAGNOSTIC_TASK_PERIOD (1000)  // 1s for diagnostics

// Global handles for our core components
static SafetyMonitor* safetyMonitor = NULL;
static RealTimeTaskManager* taskManager = NULL;
static CRRobotArmManager* robotArm = NULL;
static CRDisplay* display = NULL;
static RobotArm* armController = NULL;
static UserInput* userInput = NULL;

// Task function prototypes
static void SafetyTask(void* parameters);
static void MotionControlTask(void* parameters);
static void MonitoringTask(void* parameters);
static void DiagnosticTask(void* parameters);

int main(void) {
    // Initialize core safety and management systems
    safetyMonitor = SafetyMonitor_Create();
    if (!safetyMonitor) {
        printf("Failed to create SafetyMonitor\n");
        return -1;
    }

    taskManager = RealTimeTaskManager_Create(safetyMonitor);
    if (!taskManager) {
        printf("Failed to create RealTimeTaskManager\n");
        SafetyMonitor_Destroy(safetyMonitor);
        return -1;
    }

    // Initialize display
    display = CRDisplay_Create();
    if (!display || !CRDisplay_Init(display)) {
        printf("Failed to initialize display\n");
        goto cleanup;
    }

    // Initialize robot arm controller
    armController = RobotArm_Create();
    if (!armController || !RobotArm_Init(armController)) {
        CRDisplay_printMsg(display, "Failed to initialize robot arm controller");
        goto cleanup;
    }

    // Initialize user input
    userInput = UserInput_Create();
    if (!userInput || !UserInput_Init(userInput)) {
        CRDisplay_printMsg(display, "Failed to initialize user input");
        goto cleanup;
    }

    // Create robot arm manager
    robotArm = CRRobotArmManager_Create(safetyMonitor, taskManager);
    if (!robotArm) {
        CRDisplay_printMsg(display, "Failed to create CRRobotArmManager");
        goto cleanup;
    }

    // Set up component relationships
    if (!CRRobotArmManager_setItsCRDisplay(robotArm, display) ||
        !CRRobotArmManager_setItsRobotArm(robotArm, armController) ||
        !CRRobotArmManager_setItsUserInput(robotArm, userInput)) {
        CRDisplay_printMsg(display, "Failed to set up component relationships");
        goto cleanup;
    }

    // Create critical real-time tasks
    if (!RealTimeTaskManager_CreateTask(taskManager, "Safety",
                                      SafetyTask, NULL,
                                      SAFETY_TASK_PRIORITY,
                                      SAFETY_STACK_SIZE)) {
        CRDisplay_printMsg(display, "Failed to create safety task");
        goto cleanup;
    }

    if (!RealTimeTaskManager_CreateTask(taskManager, "Motion",
                                      MotionControlTask, NULL,
                                      MOTION_TASK_PRIORITY,
                                      MOTION_STACK_SIZE)) {
        CRDisplay_printMsg(display, "Failed to create motion task");
        goto cleanup;
    }

    if (!RealTimeTaskManager_CreateTask(taskManager, "Monitor",
                                      MonitoringTask, NULL,
                                      MONITORING_TASK_PRIORITY,
                                      MONITOR_STACK_SIZE)) {
        CRDisplay_printMsg(display, "Failed to create monitoring task");
        goto cleanup;
    }

    if (!RealTimeTaskManager_CreateTask(taskManager, "Diagnostic",
                                      DiagnosticTask, NULL,
                                      DIAGNOSTIC_TASK_PRIORITY,
                                      DIAGNOSTIC_STACK_SIZE)) {
        CRDisplay_printMsg(display, "Failed to create diagnostic task");
        goto cleanup;
    }

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    return 0;

cleanup:
    if (robotArm) CRRobotArmManager_Destroy(robotArm);
    if (armController) RobotArm_Destroy(armController);
    if (userInput) UserInput_Destroy(userInput);
    if (display) CRDisplay_Destroy(display);
    if (taskManager) RealTimeTaskManager_Destroy(taskManager);
    if (safetyMonitor) SafetyMonitor_Destroy(safetyMonitor);
    return -1;
}

static void SafetyTask(void* parameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    
    while (1) {
        // Check safety constraints
        if (!CRRobotArmManager_CheckSafetyConstraints(robotArm)) {
            SafetyMonitor_LogError(safetyMonitor, "Safety constraints violated", DIAG_ERROR);
            CRRobotArmManager_EmergencyStop(robotArm);
        }
        
        // Check for emergency stop requests
        if (UserInput_isEmergencyStopRequested(userInput)) {
            CRRobotArmManager_EmergencyStop(robotArm);
            CRDisplay_printMsg(display, "Emergency stop initiated by user");
            UserInput_clearEmergencyStop(userInput);
        }
        
        // Reset watchdog
        SafetyMonitor_ResetWatchdog(safetyMonitor);
        
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(SAFETY_TASK_PERIOD));
    }
}

static void MotionControlTask(void* parameters) {
    MotionCommand cmd;
    TickType_t lastWakeTime = xTaskGetTickCount();
    
    while (1) {
        // Get and process motion commands
        if (UserInput_getMotionCommand(userInput, &cmd) == INPUT_VALID) {
            if (UserInput_validateMotionCommand(userInput, &cmd) == INPUT_VALID) {
                Position3D target = {cmd.x, cmd.y, cmd.z};
                
                if (CRRobotArmManager_PlanMotion(robotArm, target)) {
                    if (CRRobotArmManager_ExecuteMotion(robotArm)) {
                        CRDisplay_printMsg(display, "Motion executed successfully");
                    } else {
                        CRDisplay_printMsg(display, "Motion execution failed");
                    }
                } else {
                    CRDisplay_printMsg(display, "Motion planning failed");
                }
            }
        }
        
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(MOTION_TASK_PERIOD));
    }
}

static void MonitoringTask(void* parameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    Position3D currentPos;
    char message[100];
    
    while (1) {
        currentPos = CRRobotArmManager_GetCurrentPosition(robotArm);
        
        snprintf(message, sizeof(message), "Position: X=%.2f, Y=%.2f, Z=%.2f", 
                currentPos.x, currentPos.y, currentPos.z);
        CRDisplay_printMsg(display, message);
        
        if (!CRRobotArmManager_IsInSafeZone(robotArm)) {
            CRDisplay_printMsgWithPriority(display, "WARNING: Robot arm near workspace limits", 
                                         DISPLAY_PRIORITY_HIGH);
        }
        
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(MONITOR_TASK_PERIOD));
    }
}

static void DiagnosticTask(void* parameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    float velocity, acceleration;
    char message[100];
    
    while (1) {
        if (CRRobotArmManager_GetDiagnostics(robotArm, &velocity, &acceleration)) {
            snprintf(message, sizeof(message), 
                    "Diagnostics - Velocity: %.2f, Acceleration: %.2f", 
                    velocity, acceleration);
            CRDisplay_printMsgWithPriority(display, message, DISPLAY_PRIORITY_LOW);
        }
        
        // Log component error counts
        snprintf(message, sizeof(message), 
                "Error counts - Display: %lu, Input: %lu", 
                CRDisplay_getErrorCount(display),
                UserInput_getErrorCount(userInput));
        CRDisplay_printMsgWithPriority(display, message, DISPLAY_PRIORITY_LOW);
        
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(DIAGNOSTIC_TASK_PERIOD));
    }
}
