//
// Created by mahon on 1/27/2024.
//

#ifndef SIMULALOCK_OPTICALSPEEDSENSOR_H
#define SIMULALOCK_OPTICALSPEEDSENSOR_H


typedef struct OpticalSpeedSensor OpticalSpeedSensor;
struct OpticalSpeedSensor
{
    int wheelSize;
    int sensitivity;
    int speed;
};

void OpticalSpeedSensor_Init(OpticalSpeedSensor* const me);
void OpticalSpeedSensor_Cleanup(OpticalSpeedSensor* const me);
OpticalSpeedSensor* OpticalSpeedSensor_Create(void);
void OpticalSpeedSensor_Destroy(OpticalSpeedSensor* const me);

void OpticalSpeedSensor_configure(OpticalSpeedSensor* const me, int wheelSize, int sensitivity);
void OpticalSpeedSensor_disable(OpticalSpeedSensor* const me);
void OpticalSpeedSensor_enable(OpticalSpeedSensor* const me);
int OpticalSpeedSensor_getSpeed(OpticalSpeedSensor* const me);

#endif //SIMULALOCK_OPTICALSPEEDSENSOR_H
