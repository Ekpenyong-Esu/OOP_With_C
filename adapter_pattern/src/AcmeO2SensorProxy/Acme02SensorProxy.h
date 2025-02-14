/**
 * @file Acme02SensorProxy.h
 * @brief Proxy implementation for Acme oxygen sensor
 * 
 * This file contains the implementation of the proxy pattern
 * for interfacing with Acme oxygen sensors.
 */

#ifndef ADAPTER_PATTERN_ACME02SENSORPROXY_H
#define ADAPTER_PATTERN_ACME02SENSORPROXY_H

#include <stdbool.h>

typedef struct AcmeO2SensorProxy AcmeO2SensorProxy;
struct AcmeO2SensorProxy
{
    unsigned int (*getO2Conc)(void);
    unsigned long (*getO2Flow)(void);
};

unsigned int getO2Conc(void);
unsigned long getO2Flow(void);

#endif // ADAPTER_PATTERN_ACME02SENSORPROXY_H
