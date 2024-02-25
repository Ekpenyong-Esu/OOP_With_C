//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATORC_ROBOT_ACTION_H
#define MEDIATORC_ROBOT_ACTION_H


#include <vector>

/* Position of robot */
struct Position {
    int x;
    int y;
    int z;
    Position(int posX = 0, int posY = 0 , int posZ = 0) : x(posX), y(posY), z(posZ)
    {}
};


class Move_cmd {
public:
    Move_cmd(char devide_id = 0, char value = 0) :
            devide_id_(devide_id), value_(value)
    {}
    ~Move_cmd() = default;;
    char get_device_id() const { return devide_id_;}
    int get_value() const { return value_;}

private:
    char devide_id_;
    int value_;
};

class Move_action {
public:
    Move_action() = default;;
    Move_action(std::vector<Move_cmd> const& action): action_(action)
    {}
    ~Move_action() = default;;
    void add_action(const Move_cmd& cmd) {
        action_.push_back(cmd);
    }

    std::vector<Move_cmd> get_action() const {
        return action_;
    }

private:
    std::vector<Move_cmd> action_;
};


#endif //MEDIATORC_ROBOT_ACTION_H
