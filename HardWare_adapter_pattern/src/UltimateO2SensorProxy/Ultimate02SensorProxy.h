//
// Created by mahon on 1/4/2024.
//

#ifndef ADAPTER_PATTERN_ULTMATE02SENSORPROXY_H
#define ADAPTER_PATTERN_ULTMATE02SENSORPROXY_H

typedef struct UltimateO2SensorProxy UltimateO2SensorProxy;
struct UltimateO2SensorProxy
{
    unsigned int (*accessO2Conc)(void);
    unsigned long (*accessGasFlow)(void);
};

unsigned int accessO2Conc();
unsigned long accessGasFlow();

#endif //ADAPTER_PATTERN_ULTMATE02SENSORPROXY_H
