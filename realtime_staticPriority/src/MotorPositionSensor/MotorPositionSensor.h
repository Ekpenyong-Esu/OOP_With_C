//
// Created by mahon on 1/25/2024.
//

#ifndef REALTIME_STATICPRIORITY_MOTORPOSITIONSENSOR_H
#define REALTIME_STATICPRIORITY_MOTORPOSITIONSENSOR_H

void MotorPositionSensor_Init(void);
void MotorPositionSensor_Cleanup(void);

void MotorPositionSensor_run(void);
void getPosition(void);

void MotorPositionSensor_initRelations(void);

#endif //REALTIME_STATICPRIORITY_MOTORPOSITIONSENSOR_H
