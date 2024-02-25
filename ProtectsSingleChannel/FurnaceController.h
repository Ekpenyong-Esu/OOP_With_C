//
// Created by mahon on 2/8/2024.
//

#ifndef PROTECTSSINGLECHANNEL_FURNACECONTROLLER_H
#define PROTECTSSINGLECHANNEL_FURNACECONTROLLER_H

typedef struct FurnaceController FurnaceController;
struct FurnaceController
{

};

void FurnaceController_emergencyRestart(FurnaceController* const me);
void FurnaceController_shutDown(FurnaceController* const me);

#endif //PROTECTSSINGLECHANNEL_FURNACECONTROLLER_H
