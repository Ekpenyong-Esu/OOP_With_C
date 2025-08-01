//
// Created by mahon on 1/25/2024.
//

#include "MotorDisplay.h"
#include "MotorData.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// Task handle for MotorDisplay
static TaskHandle_t motorDisplayTaskHandle = NULL;

// Function prototypes
static void MotorDisplayTask(void *pvParameters);

void MotorDisplay_Init(void) {
    // Create the MotorDisplay task with static priority
    xTaskCreate(MotorDisplayTask, "MotorDisplay", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &motorDisplayTaskHandle);
}

void MotorDisplay_Cleanup(void) {
    // Delete the MotorDisplay task
    if (motorDisplayTaskHandle != NULL) {
        vTaskDelete(motorDisplayTaskHandle);
    }
}

static void MotorDisplayTask(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        printf("Commanded position = %d\n", getCmdPos());
        printf("Measured position  = %d\n\n", getMeasPos());
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500ms
    }
}
