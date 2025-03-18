//
// Created by mahon on 1/13/2024.
//

#ifndef UNTITLED1_LED_H
#define UNTITLED1_LED_H

#define LED_ON 1
#define LED_OFF 0

typedef struct LED LED;
struct LED
{
    int LEDStatus;
};

void LED_Init(LED* const me);
void LED_Cleanup(LED* const me);

LED* LED_Create(void);
void LED_Destroy(LED* const me);

void LED_LightOn(LED* const me);
void LED_LightOff(LED* const me);

#endif //UNTITLED1_LED_H
