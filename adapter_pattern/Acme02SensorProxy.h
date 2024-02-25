//
// Created by mahon on 1/4/2024.
//

#ifndef ADAPTER_PATTERN_ACME02SENSORPROXY_H
#define ADAPTER_PATTERN_ACME02SENSORPROXY_H

typedef struct AcmeO2SensorProxy AcmeO2SensorProxy;
struct AcmeO2SensorProxy
{
    unsigned int (*getO2Conc)(void);
    unsigned long (*getO2Flow)(void);
};

unsigned int getO2Conc();
unsigned long getO2Flow();

#endif //ADAPTER_PATTERN_ACME02SENSORPROXY_H
