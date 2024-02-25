//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATORC_MOTOR_H
#define MEDIATORC_MOTOR_H


#include <iostream>

class Motor{

public:
    Motor() : motor_id_(0), value_(0)
    {}
    Motor(int motor_id, int value) : motor_id_(motor_id), value_(value)
    {}
    virtual ~Motor() = default;
    virtual void move(int value) {std::cout << "move" <<std::endl;};

    int get_value() const { return value_;}
protected:
    int motor_id_;
    int   value_;

};


#endif //MEDIATORC_MOTOR_H
