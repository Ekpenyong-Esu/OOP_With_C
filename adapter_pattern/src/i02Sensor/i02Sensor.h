//
// Created by mahon on 1/4/2024.
//

#ifndef ADAPTER_PATTERN_I02SENSOR_H
#define ADAPTER_PATTERN_I02SENSOR_H

typedef struct iO2Sensor iO2Sensor;
struct iO2Sensor
{
    int (*gimmeO2Flow)(void);
    int (*gimmeO2Conc)(void);
};

#endif //ADAPTER_PATTERN_I02SENSOR_H
