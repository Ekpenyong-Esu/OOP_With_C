//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_STATICPRIORITY_MOTORCONTROLLER_H
#define REALTIME_STATICPRIORITY_MOTORCONTROLLER_H

void MotorController_Init(void);
void MotorController_Cleanup(void);

void MotorController_run(void);
void move(void);
void zero(void);

void MotorController_initRelations(void);

#endif //REALTIME_STATICPRIORITY_MOTORCONTROLLER_H
