#include "../include/Task.h"
#include <stdio.h>


int main() {
    // Creating tasks
    Task *basicTask =
            createTaskWithType(BASIC, 1, "Basic Task", "This is a basic task", 2);
    Task *urgentTask =
            createTaskWithType(URGENT, 2, "Urgent Task", "This is an urgent task", 1);

    // Displaying tasks
    displayTask(basicTask);
    printf("\n");
    displayTask(urgentTask);

    // Destroying tasks
    destroyTask(basicTask);
    destroyTask(urgentTask);

    return 0;
}
