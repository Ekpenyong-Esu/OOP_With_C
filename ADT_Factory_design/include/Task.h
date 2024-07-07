//
// Created by mahon on 3/9/2024.
//

#ifndef ADT_FACTORY_DESIGN_TASK_H
#define ADT_FACTORY_DESIGN_TASK_H


#include <stdbool.h>

// Task ADT
typedef struct {
    int id;
    char title[50];
    char description[100];
    int priority;
    bool completed;
} Task;

Task *createTask(int id, const char *title, const char *description,
                 int priority);

void destroyTask(Task *task);
void displayTask(Task *task);

// Factory Method
typedef enum { BASIC, URGENT } TaskType;

Task *createTaskWithType(TaskType type, int id, const char *title,
                         const char *description, int priority);

#endif //ADT_FACTORY_DESIGN_TASK_H
