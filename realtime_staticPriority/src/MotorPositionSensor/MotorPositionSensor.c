//
// Created by mahon on 1/25/2024.
//

#include "MotorPositionSensor.h"
#include "MotorData.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

// Task handle for MotorPositionSensor
static TaskHandle_t motorPositionSensorTaskHandle = NULL;

// Function prototypes
static void MotorPositionSensorTask(void *pvParameters);

void MotorPositionSensor_Init(void) {
    // Create the MotorPositionSensor task with static priority
    xTaskCreate(MotorPositionSensorTask, "MotorPositionSensor", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, &motorPositionSensorTaskHandle);
}

void MotorPositionSensor_Cleanup(void) {
    // Delete the MotorPositionSensor task
    if (motorPositionSensorTaskHandle != NULL) {
        vTaskDelete(motorPositionSensorTaskHandle);
    }
}

static void MotorPositionSensorTask(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        int position = rand() % 100; // Simulate sensor reading
        setMeasPos(position);
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50ms
    }
}
