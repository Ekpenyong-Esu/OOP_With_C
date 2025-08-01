#ifndef REAL_TIME_TASK_MANAGER_H
#define REAL_TIME_TASK_MANAGER_H

#include "config.h"
#include "SafetyMonitor.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdbool.h>

#define MAX_TASKS 10

typedef enum {
    TASK_IDLE = 0,
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED
} TaskState;

typedef struct {
    TaskHandle_t handle;
    const char* name;
    UBaseType_t priority;
    TaskState state;
    TickType_t lastWakeTime;
    uint32_t executionCount;
    uint32_t overruns;
} TaskInfo;

typedef struct RealTimeTaskManager {
    SafetyMonitor* safetyMonitor;
    TaskInfo tasks[MAX_TASKS];
    uint8_t taskCount;
    bool isInitialized;
} RealTimeTaskManager;

// Lifecycle Management
RealTimeTaskManager* RealTimeTaskManager_Create(SafetyMonitor* safetyMonitor);
void RealTimeTaskManager_Destroy(RealTimeTaskManager* const me);
bool RealTimeTaskManager_Init(RealTimeTaskManager* const me);

// Task Management
bool RealTimeTaskManager_CreateTask(
    RealTimeTaskManager* const me,
    const char* name,
    TaskFunction_t taskFunction,
    void* parameters,
    UBaseType_t priority,
    uint32_t stackSize
);

bool RealTimeTaskManager_SuspendTask(RealTimeTaskManager* const me, const char* name);
bool RealTimeTaskManager_ResumeTask(RealTimeTaskManager* const me, const char* name);
bool RealTimeTaskManager_DeleteTask(RealTimeTaskManager* const me, const char* name);

// Monitoring and Control
TaskInfo* RealTimeTaskManager_GetTaskInfo(RealTimeTaskManager* const me, const char* name);
bool RealTimeTaskManager_MonitorDeadlines(RealTimeTaskManager* const me);
void RealTimeTaskManager_ResetStatistics(RealTimeTaskManager* const me);

#endif // REAL_TIME_TASK_MANAGER_H