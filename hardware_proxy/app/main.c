#include <stdint.h>
#include <stdio.h>
#include "MotorProxy.h"

int main(int argc, char const *argv[])
{
    /* code */
    MotorProxy * motor = MotorProxy_Create();
    // config rotaryArmLength and motor address
    unsigned int rotaryArmLength = 10;
    uint32_t location = (*(uint32_t *)0x396a2730);
    unsigned int motorData = 100;

    
    //  // Allocate memory for motor control
    // unsigned int rotaryArmLength = 10;
    // unsigned int *location = (unsigned int *)malloc(sizeof(unsigned int));
    // unsigned int *motorData = (unsigned int *)malloc(sizeof(unsigned int));
    
    // // Initialize allocated memory
    // *location = 0;
    // *motorData = 100;


    DirectionType direction;
    unsigned int speed;

    MotorProxy_configure(motor, rotaryArmLength, &location, &motorData);
    MotorProxy_initialize(motor);
    MotorProxy_enable(motor);

    direction = FORWARD;
    speed = 10;
    MotorProxy_writeMotorSpeed(motor, direction, speed);
    DirectionType getdirection = MotorProxy_accessMotorDirection(motor);
    unsigned int getspeed = MotorProxy_accessMotorSpeed(motor);
    unsigned int getstate = MotorProxy_aceessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    direction = REVERSE;
    speed = 20;
    MotorProxy_writeMotorSpeed(motor, direction, speed);
    getdirection = MotorProxy_accessMotorDirection(motor);
    getspeed = MotorProxy_accessMotorSpeed(motor);
    getstate = MotorProxy_aceessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    MotorProxy_disable(motor);
    getdirection = MotorProxy_accessMotorDirection(motor);
    getspeed = MotorProxy_accessMotorSpeed(motor);
    getstate = MotorProxy_aceessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    MotorProxy_Destroy(motor);
    // free(location);
    // free(motorData);

    return 0;
}
