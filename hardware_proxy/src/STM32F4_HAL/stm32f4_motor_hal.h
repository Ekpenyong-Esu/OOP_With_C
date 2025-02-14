#ifndef STM32F4_MOTOR_HAL_H
#define STM32F4_MOTOR_HAL_H

#include "stm32f4xx_hal.h"

// Motor GPIO definitions
#define MOTOR_PORT GPIOA
#define MOTOR_PIN_IN1 GPIO_PIN_0
#define MOTOR_PIN_IN2 GPIO_PIN_1
#define MOTOR_PIN_EN  GPIO_PIN_2

// PWM Timer definitions
#define MOTOR_TIMER htim2
#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1

void STM32F4_Motor_Init(void);
void STM32F4_Motor_SetPWM(uint32_t speed);
void STM32F4_Motor_SetDirection(uint8_t direction);
uint32_t STM32F4_Motor_GetStatus(void);

#endif
