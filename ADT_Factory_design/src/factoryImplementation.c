//
// Created by mahon on 3/9/2024.
//
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Task* createTask(int id, const char* title, const char* description, int priority) {
    Task* task = (Task*)malloc(sizeof(Task));
    if (task != NULL) {
        task->id = id;
        strncpy_s(task->title, sizeof(task->title), title,
                  sizeof(task->title) - 1);
        strncpy_s(task->description, sizeof(task->description),  description,
                  sizeof(task->description) - 1);
        task->priority = priority;
        task->completed = false;
    }
    return task;
}

void destroyTask(Task* task) {
    free(task);
}

void displayTask(Task* task) {
    printf("Task ID: %d\n", task->id);
    printf("Title: %s\n", task->title);
    printf("Description: %s\n", task->description);
    printf("Priority: %d\n", task->priority);
    printf("Completed: %s\n", task->completed ? "Yes" : "No");
}

Task* createTaskWithType(TaskType type, int id, const char* title, const char* description, int priority) {
    Task* task = NULL;
    switch (type) {
        case BASIC:
            task = createTask(id, title, description, priority);
            break;
        case URGENT:
            task = createTask(id, title, description, priority + 1); // Higher priority for urgent tasks
            break;
    }
    return task;
}
