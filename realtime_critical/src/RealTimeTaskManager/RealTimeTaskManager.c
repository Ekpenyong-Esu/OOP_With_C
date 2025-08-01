#include "RealTimeTaskManager.h"
#include <string.h>
#include <stdlib.h>

static TaskInfo* findTask(RealTimeTaskManager* const me, const char* name) {
    if (!me || !name) return NULL;
    
    for (int i = 0; i < me->taskCount; i++) {
        if (strcmp(me->tasks[i].name, name) == 0) {
            return &me->tasks[i];
        }
    }
    return NULL;
}

RealTimeTaskManager* RealTimeTaskManager_Create(SafetyMonitor* safetyMonitor) {
    if (!safetyMonitor) return NULL;

    RealTimeTaskManager* me = (RealTimeTaskManager*)malloc(sizeof(RealTimeTaskManager));
    if (me) {
        me->safetyMonitor = safetyMonitor;
        RealTimeTaskManager_Init(me);
    }
    return me;
}

bool RealTimeTaskManager_Init(RealTimeTaskManager* const me) {
    if (!me) return false;

    me->taskCount = 0;
    me->isInitialized = true;
    memset(me->tasks, 0, sizeof(me->tasks));
    return true;
}

void RealTimeTaskManager_Destroy(RealTimeTaskManager* const me) {
    if (!me) return;

    // Safely stop all tasks before destroying
    for (int i = 0; i < me->taskCount; i++) {
        if (me->tasks[i].handle) {
            vTaskSuspend(me->tasks[i].handle);
            vTaskDelete(me->tasks[i].handle);
        }
    }

    free(me);
}

bool RealTimeTaskManager_CreateTask(
    RealTimeTaskManager* const me,
    const char* name,
    TaskFunction_t taskFunction,
    void* parameters,
    UBaseType_t priority,
    uint32_t stackSize
) {
    if (!me || !name || !taskFunction || me->taskCount >= MAX_TASKS) {
        return false;
    }

    // Check if task already exists
    if (findTask(me, name)) {
        return false;
    }

    TaskInfo* newTask = &me->tasks[me->taskCount];
    newTask->name = name;
    newTask->priority = priority;
    newTask->state = TASK_READY;
    newTask->lastWakeTime = xTaskGetTickCount();
    newTask->executionCount = 0;
    newTask->overruns = 0;

    BaseType_t result = xTaskCreate(
        taskFunction,
        name,
        stackSize,
        parameters,
        priority,
        &newTask->handle
    );

    if (result == pdPASS) {
        me->taskCount++;
        return true;
    }

    return false;
}

bool RealTimeTaskManager_SuspendTask(RealTimeTaskManager* const me, const char* name) {
    TaskInfo* task = findTask(me, name);
    if (!task || !task->handle) return false;

    vTaskSuspend(task->handle);
    task->state = TASK_SUSPENDED;
    return true;
}

bool RealTimeTaskManager_ResumeTask(RealTimeTaskManager* const me, const char* name) {
    TaskInfo* task = findTask(me, name);
    if (!task || !task->handle) return false;

    vTaskResume(task->handle);
    task->state = TASK_READY;
    return true;
}

bool RealTimeTaskManager_DeleteTask(RealTimeTaskManager* const me, const char* name) {
    TaskInfo* task = findTask(me, name);
    if (!task || !task->handle) return false;

    vTaskDelete(task->handle);
    
    // Compact the task array
    int taskIndex = task - me->tasks;
    for (int i = taskIndex; i < me->taskCount - 1; i++) {
        me->tasks[i] = me->tasks[i + 1];
    }
    me->taskCount--;
    
    return true;
}

TaskInfo* RealTimeTaskManager_GetTaskInfo(RealTimeTaskManager* const me, const char* name) {
    return findTask(me, name);
}

bool RealTimeTaskManager_MonitorDeadlines(RealTimeTaskManager* const me) {
    if (!me || !me->isInitialized) return false;

    TickType_t currentTime = xTaskGetTickCount();
    bool deadlinesMet = true;

    taskENTER_CRITICAL();
    
    for (int i = 0; i < me->taskCount; i++) {
        TaskInfo* task = &me->tasks[i];
        
        if (task->state == TASK_RUNNING) {
            TickType_t executionTime = currentTime - task->lastWakeTime;
            
            // Check for deadline overrun based on priority
            TickType_t deadline;
            switch (task->priority) {
                case RT_PRIORITY_HIGH:
                    deadline = pdMS_TO_TICKS(50);  // 50ms for high priority
                    break;
                case RT_PRIORITY_MEDIUM:
                    deadline = pdMS_TO_TICKS(100); // 100ms for medium priority
                    break;
                default:
                    deadline = pdMS_TO_TICKS(200); // 200ms for low priority
                    break;
            }
            
            if (executionTime > deadline) {
                task->overruns++;
                deadlinesMet = false;
                
                if (me->safetyMonitor) {
                    SafetyMonitor_LogError(me->safetyMonitor, 
                        "Task deadline exceeded", DIAG_WARNING);
                }
            }
        }
        task->executionCount++;
    }
    
    taskEXIT_CRITICAL();
    
    return deadlinesMet;
}

void RealTimeTaskManager_ResetStatistics(RealTimeTaskManager* const me) {
    if (!me) return;

    taskENTER_CRITICAL();
    
    for (int i = 0; i < me->taskCount; i++) {
        me->tasks[i].executionCount = 0;
        me->tasks[i].overruns = 0;
        me->tasks[i].lastWakeTime = xTaskGetTickCount();
    }
    
    taskEXIT_CRITICAL();
}