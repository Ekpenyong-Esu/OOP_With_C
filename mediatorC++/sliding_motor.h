//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATORC_SLIDING_MOTOR_H
#define MEDIATORC_SLIDING_MOTOR_H

#include <iostream>
#include "motor.h"

class Motor;

class Sliding_motor : public Motor {
public:
    Sliding_motor() : Motor()
    {}
    Sliding_motor(char motor_id, int value) : Motor(motor_id, value)
    {}
    void move(int value) {
        value_ += value;
        std::cout << "ID: " << motor_id_ << " sliding value: " << value << " current value : " << value_ << std::endl;
    }

};

#endif //MEDIATORC_SLIDING_MOTOR_H
