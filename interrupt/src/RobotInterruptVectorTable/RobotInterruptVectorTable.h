//
// Created by mahon on 1/13/2024.
//

#ifndef UNTITLED1_ROBOTINTERRUPTVECTORTABLE_H
#define UNTITLED1_ROBOTINTERRUPTVECTORTABLE_H

//typedef void* ButtonVectorPtr;
#include "ButtonHandler.h"

ButtonVectorPtr ISRAddress[10];
ButtonVectorPtr oldVectors[10];

#endif //UNTITLED1_ROBOTINTERRUPTVECTORTABLE_H
