//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATORC_ROBOT_ARM_MANAGER_H
#define MEDIATORC_ROBOT_ARM_MANAGER_H


#include "robot_action.h"
#include "motor.h"
#include <vector>

class Robot_arm_manager {
public:
    Robot_arm_manager() : curr_position_(), joints_(), path_()
    {}
    Robot_arm_manager(Position pos, const std::vector<Motor*>& joints) {
        curr_position_ = pos;
        joints_ = joints;
    }
    ~Robot_arm_manager();

    Position get_current_pos();
    void goto_position(Position goal);
    void goto_origin();

private:
    void compute_path(Position goal); // Compute path to go to goal
    Position curr_position_;
    std::vector<Motor*> joints_;
    std::vector<Move_action> path_;
};


#endif //MEDIATORC_ROBOT_ARM_MANAGER_H
