//
// Created by mahon on 1/13/2024.
//

#ifndef UNTITLED1_BUTTONHANDLER_H
#define UNTITLED1_BUTTONHANDLER_H

typedef void (*ButtonVectorPtr)(void);
struct LED;

extern ButtonVectorPtr oldVectors[10];
extern ButtonVectorPtr ISRAddress[10];

/* Operations */
void install(void);
void deinstall(void);

void handleButtonPushInterrupt(void);
void handleButtonReleaseInterrupt(void);

struct LED* ButtonHandler_getItsLED(void);
void ButtonHandler_setItsLED(struct LED* p_LED);

#endif //UNTITLED1_BUTTONHANDLER_H
