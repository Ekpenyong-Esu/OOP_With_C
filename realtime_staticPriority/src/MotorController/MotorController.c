//
// Created by mahon on 1/25/2024.
//

#include "MotorController.h"
#include "MotorData.h"
#include "FreeRTOS.h"
#include "task.h"

// Task handle for MotorController
static TaskHandle_t motorControllerTaskHandle = NULL;

// Motor positions
static int motor1Pos = 0;
static int motor2Pos = 0;

// Function prototypes
static void MotorControllerTask(void *pvParameters);
static void move(void);
static void zero(void);

void MotorController_Init(void) {
    // Create the MotorController task with static priority
    xTaskCreate(MotorControllerTask, "MotorController", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, &motorControllerTaskHandle);
}

void MotorController_Cleanup(void) {
    // Delete the MotorController task
    if (motorControllerTaskHandle != NULL) {
        vTaskDelete(motorControllerTaskHandle);
    }
}

static void MotorControllerTask(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        move();
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100ms
    }
}

static void move(void) {
    // Simulate reading motor positions
    motor1Pos = rand() % 100;
    motor2Pos = rand() % 100;

    // Update command position
    setCmdPos(100 * motor1Pos + motor2Pos);
}

static void zero(void) {
    // Reset motor positions
    motor1Pos = 0;
    motor2Pos = 0;
    setCmdPos(0);
}
