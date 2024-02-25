//
// Created by mahon on 1/13/2024.
//
#include "stm32f4xx_hal.h"

// LED structure
typedef struct {
    GPIO_TypeDef* port;  // GPIO port (e.g., GPIOA, GPIOB, ...)
    uint16_t pin;        // GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, ...)
} LED;

// Function to initialize an LED
void initLED(LED* led) {
    // Additional initialization logic if needed
}

// Function to turn on the LED
void turnOnLED(LED* led) {
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
}

// Function to turn off the LED
void turnOffLED(LED* led) {
    HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
}

// Function to toggle the LED state
void toggleLED(LED* led) {
    HAL_GPIO_TogglePin(led->port, led->pin);
}

// Example usage
int main(void) {
    // Initialize the HAL Library
    HAL_Init();

    // System Clock Configuration
    SystemClock_Config();

    // Initialize LED GPIO
    LED myLED;
    myLED.port = GPIOA;
    myLED.pin = GPIO_PIN_5; // Assuming you connected the LED to GPIOA_PIN_5

    initLED(&myLED);

    while (1) {
        // Use LED functions to control the LED
        turnOnLED(&myLED);
        HAL_Delay(1000);  // Delay for 1 second
        turnOffLED(&myLED);
        HAL_Delay(1000);  // Delay for 1 second
        toggleLED(&myLED);
        HAL_Delay(1000);  // Delay for 1 second
    }
}
