//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATORC_ROTATING_MOTOR_H
#define MEDIATORC_ROTATING_MOTOR_H

#include <iostream>
#include "motor.h"

class Motor;

class  Rotating_motor : public Motor
{
public:
    Rotating_motor() : Motor()
    {}
    Rotating_motor(char motor_id, int value) : Motor(motor_id, value)
    {}
    void move(int value) override {
        value_ += value;
        std::cout << "ID: " << motor_id_ << " rotating value: " << value << " current value : " << value_ << std::endl;

    }

};

#endif //MEDIATORC_ROTATING_MOTOR_H
