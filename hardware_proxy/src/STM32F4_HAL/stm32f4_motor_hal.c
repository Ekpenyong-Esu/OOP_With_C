#include "stm32f4_motor_hal.h"

void STM32F4_Motor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // Enable GPIO clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // Configure motor control pins
    GPIO_InitStruct.Pin = MOTOR_PIN_IN1 | MOTOR_PIN_IN2 | MOTOR_PIN_EN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);
    
    // Timer configuration is assumed to be done in CubeMX
}

void STM32F4_Motor_SetPWM(uint32_t speed) {
    // Set PWM duty cycle
    __HAL_TIM_SET_COMPARE(&MOTOR_TIMER, MOTOR_PWM_CHANNEL, speed);
}

void STM32F4_Motor_SetDirection(uint8_t direction) {
    switch(direction) {
        case 1: // FORWARD
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN2, GPIO_PIN_RESET);
            break;
        case 2: // REVERSE
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN2, GPIO_PIN_SET);
            break;
        default: // NO_DIRECTION
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_IN2, GPIO_PIN_RESET);
    }
}

uint32_t STM32F4_Motor_GetStatus(void) {
    // Return motor status (can be expanded based on needs)
    return HAL_GPIO_ReadPin(MOTOR_PORT, MOTOR_PIN_EN);
}
