#include "RotatingArmJoint.h"

int RotatingArmJoint_getRotation(RotatingArmJoint* const me){
    return me->angle;
}
int RotatingArmJoint_rotate(RotatingArmJoint* const me, int x){
    me->angle = x;
    return 0;
}
int RotatingArmJoint_zero(RotatingArmJoint* const me){
    me->angle = 0;
    return 0;
}
