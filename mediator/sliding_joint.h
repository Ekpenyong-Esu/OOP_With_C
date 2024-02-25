//
// Created by mahon on 1/8/2024.
//

#ifndef MEDIATOR_SLIDING_JOINT_H
#define MEDIATOR_SLIDING_JOINT_H

typedef struct sliding_joint_t sliding_joint_t;
struct sliding_joint_t {
    int value;
    char devide_id;
};

void sliding_joint_init(sliding_joint_t* const me);
void sliding_joint_cleanup(sliding_joint_t* const me);

sliding_joint_t* sliding_joint_create();
void sliding_joint_destroy(sliding_joint_t* const me);

void sliding_joint_config(sliding_joint_t* const me, char devide_id);

void sliding_joint_move ( sliding_joint_t* const me, int value);
int  sliding_joint_get_value(sliding_joint_t* const me);

#endif //MEDIATOR_SLIDING_JOINT_H
