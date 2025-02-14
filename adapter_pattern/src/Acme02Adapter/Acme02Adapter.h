//
// Created by mahon on 1/4/2024.
//

#ifndef ADAPTER_PATTERN_ACME02ADATER_H
#define ADAPTER_PATTERN_ACME02ADATER_H

#include "i02Sensor.h"
#include "Acme02SensorProxy.h"


typedef struct AcmeO2Adapter AcmeO2Adapter;
struct AcmeO2Adapter
{
    iO2Sensor* iO2Sensor;
    AcmeO2SensorProxy* itsAcmeO2SensorProxy;
};

void AcmeO2Adapter_Init(AcmeO2Adapter* const me);
void AcmeO2Adapter_Cleanup(AcmeO2Adapter* const me);

AcmeO2Adapter* AcmeO2Adapter_Create(void);
void AcmeO2Adapter_Destroy(AcmeO2Adapter* me);

int AcmeO2Adapter_gimmeO2Conc(AcmeO2Adapter* const me);
int AcmeO2Adapter_gimmeO2Flow(AcmeO2Adapter* const me);

#endif //ADAPTER_PATTERN_ACME02ADATER_H
