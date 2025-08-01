//
// Created by mahon on 1/25/2024.
//
#include <stdio.h>
#include <stdbool.h>  // For using 'true' and 'false' keywords

// Function prototypes for tasks and POST
static bool POST(void);
static void task1(void);
static void task2(void);
static void task3(void);

/**
 * @brief Main entry point of the program
 * 
 * Initializes the system and runs the cyclic executive loop.
 * 
 * @return int Exit status (0 for success)
 */
int main(void) {
    // Global static and stack data
    static const int nTasks = 3;  // Number of tasks in the system
    int currentTask = 0;         // Index of the current task

    // Perform Power-On Self-Test (POST)
    if (POST()) {
        // Scheduling executive loop
        while (true) {
            task1();
            task2();
            task3();
        }  // End cyclic processing loop
    } else {
        // POST failed, handle error (e.g., log and exit)
        fprintf(stderr, "POST failed. System cannot start.\n");
        return 1;  // Non-zero exit code indicates failure
    }

    return 0;  // Success
}

/**
 * @brief Perform Power-On Self-Test (POST)
 * 
 * Simulates a POST check to ensure the system is ready to run.
 * 
 * @return bool True if POST succeeds, false otherwise
 */
static bool POST(void) {
    // Simulate POST success
    return true;
}

/**
 * @brief Task 1 execution logic
 */
static void task1(void) {
    // Simulate task 1 processing
    printf("Task 1 is running.\n");
}

/**
 * @brief Task 2 execution logic
 */
static void task2(void) {
    // Simulate task 2 processing
    printf("Task 2 is running.\n");
}

/**
 * @brief Task 3 execution logic
 */
static void task3(void) {
    // Simulate task 3 processing
    printf("Task 3 is running.\n");
}
