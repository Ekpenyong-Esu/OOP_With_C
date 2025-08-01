
#include "MotorController.h"
#include "MotorDisplay.h"
#include "MotorPositionSensor.h"
#include "FreeRTOS.h"
#include "task.h"

int main(void) {
    // Initialize all modules
    MotorController_Init();
    MotorDisplay_Init();
    MotorPositionSensor_Init();

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // The program should never reach here
    for (;;) {
    }

    return 0;
}
