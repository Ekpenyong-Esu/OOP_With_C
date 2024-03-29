//
// Created by mahon on 2/8/2024.
//

#ifndef PROTECTSSINGLECHANNEL_CHECKTEMPERATURE_H
#define PROTECTSSINGLECHANNEL_CHECKTEMPERATURE_H

struct FurnaceController;

typedef struct CheckTemperature CheckTemperature;
struct CheckTemperature {
    int maximumTemp;
    int minimumTemp;
    struct FurnaceController* itsFurnaceController;
};

void CheckTemperature_Init(CheckTemperature* const me);

void CheckTemperature_Cleanup(CheckTemperature* const me);

void CheckTemperature_checkTemperature(CheckTemperature* const me, int temp);

struct FurnaceController* CheckTemperature_getItsFurnaceController(const CheckTemperature* const me);

void CheckTemperature_setItsFurnaceController(CheckTemperature* const me, struct FurnaceController* p_FurnaceController);

CheckTemperature * CheckTemperature_Create(void);

void CheckTemperature_Destroy(CheckTemperature* const me);

#endif //PROTECTSSINGLECHANNEL_CHECKTEMPERATURE_H
