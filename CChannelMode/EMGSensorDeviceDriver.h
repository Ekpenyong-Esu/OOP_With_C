//
// Created by mahon on 2/8/2024.
//

#ifndef CCHANNELMODE_EMGSENSORDEVICEDRIVER_H
#define CCHANNELMODE_EMGSENSORDEVICEDRIVER_H


typedef struct EMGSensorDeviceDriver EMGSensorDeviceDriver;
struct EMGSensorDeviceDriver
{
    int sen;
    int voltage;
};

/* Constructors and destructors:*/
void EMGSensorDeviceDriver_Init(EMGSensorDeviceDriver* const me);
void EMGSensorDeviceDriver_Cleanup(EMGSensorDeviceDriver* const me);

/* Operations */

EMGSensorDeviceDriver * EMGSensorDeviceDriver_Create(void);
void EMGSensorDeviceDriver_Destroy(EMGSensorDeviceDriver* const me);

void EMGSensorDeviceDriver_setSensitivity(EMGSensorDeviceDriver* const me, int sen);
void EMGSensorDeviceDriver_acquireData(EMGSensorDeviceDriver* const me);

void EMGSensorDeviceDriver_setItsConvertToFrequency(EMGSensorDeviceDriver* const me, ConvertToFrequency* const p_ConvertToFrequency);

#endif //CCHANNELMODE_EMGSENSORDEVICEDRIVER_H
