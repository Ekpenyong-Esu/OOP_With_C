//
// Created by mahon on 1/4/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "MotorData.h"
#include "MotorProxy.h"

/* class MotorProxy */
/* This function takes a MotorData structure and creates  */
/* a device-specific unsigned int in device native format. */
static unsigned int marshal(const struct MotorData mData);

static struct MotorData unmarshal(unsigned int encodedMData);

void MotorProxy_Init(MotorProxy* const me) {
    me->motorAddr = NULL;
    me->motorData = NULL;
    me->rotaryArmLength = 0;
}

void MotorProxy_Cleanup(MotorProxy* const me) {
    // do nothing
}

DirectionType MotorProxy_accessMotorDirection(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;
    mData = unmarshal(*me->motorAddr);
    return mData.direction;
}

unsigned int MotorProxy_accessMotorSpeed(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;
    mData = unmarshal(*me->motorAddr);
    return mData.speed;
}

unsigned int MotorProxy_aceessMotorState(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;
    mData = unmarshal(*me->motorAddr);
    return mData.errorStatus;
}

void MotorProxy_clearErrorStatus(MotorProxy* const me) {
    if (!me->motorData)
        return;
    *me->motorAddr &= 0xFF;
}

void MotorProxy_configure(MotorProxy* const me, unsigned int length, unsigned int* location, unsigned int* motorData) {
    me->rotaryArmLength = length;
    me->motorAddr = location;
    me->motorData = motorData;
    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void MotorProxy_disable(MotorProxy* const me) {
    // and with all bits set except for the enable bit
    if (!me->motorData)
        return;
    *me->motorData &= 0xFFFE;
}

void MotorProxy_enable(MotorProxy* const me) {
    if (!me->motorData)
        return;
    *me->motorAddr |= 1;
    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void MotorProxy_initialize(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return;
    mData.on_off = 1;
    mData.direction = 0;
    mData.speed = 0;
    mData.errorStatus = 0;
    mData.noPowerError = 0;
    mData.noTorqueError = 0;
    mData.BITError = 0;
    mData.overTemperatureError = 0;
    mData.reservedError1 = 0;
    mData.reservedError2 = 0;
    mData.unknownError = 0;
    *me->motorAddr = marshal(mData);
    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
}

void MotorProxy_writeMotorSpeed(MotorProxy* const me, const DirectionType direction, unsigned int speed) {
    MotorData mData;
    double dPi, dArmLength, dSpeed, dAdjSpeed;

    if (!me->motorData) return;
    mData = unmarshal(*me->motorAddr);
    mData.direction = direction;

    // ok, let's do some math to adjust for
    // the length of the rotary arm times 10
    if (me->rotaryArmLength > 0) {
        dSpeed = speed;
        dArmLength = me->rotaryArmLength;
        dAdjSpeed = dSpeed / 2.0 / 3.14159 / dArmLength * 10.0;
        mData.speed = (int)dAdjSpeed;
    }
    else
    {
        mData.speed = speed;
    }
    *me->motorData = marshal(mData);
    printf("%s, %d, %p\n", __func__, *me->motorAddr, me->motorAddr);
    return;
}

static unsigned int marshal(const struct MotorData mData) {
    unsigned int deviceCmd;
    deviceCmd = 0; // set all bits to zero
    if (mData.on_off)
        deviceCmd |= 1; // OR in the appropriate bit

    if (mData.direction == FORWARD)
        deviceCmd |= (2 << 1);
    else if (mData.direction == REVERSE)
        deviceCmd |= (1 << 1);

    if (mData.speed < 32 && mData.speed >= 0)
        deviceCmd |= mData.speed << 3;

    if (mData.errorStatus)
        deviceCmd |= 1 << 8;

    if (mData.noPowerError)
        deviceCmd |= 1 << 9;

    if (mData.noTorqueError)
        deviceCmd |= 1 << 10;

    if (mData.BITError)
        deviceCmd |= 1 << 11;

    if (mData.overTemperatureError)
        deviceCmd |= 1 << 12;

    if (mData.reservedError1)
        deviceCmd |= 1 << 13;

    if (mData.reservedError2)
        deviceCmd |= 1 << 14;

    if (mData.unknownError)
        deviceCmd |= 1 << 15;

    return deviceCmd;
}

static struct MotorData unmarshal(unsigned int encodedMData) {
    printf("%s, %d\n", __func__, encodedMData);
    MotorData mData;
    int temp;

    mData.on_off = encodedMData & 1;

    temp = (encodedMData & (3 << 1)) >> 1;
    if (temp == 1)
        mData.direction = REVERSE;
    else if (temp == 2)
        mData.direction = FORWARD;
    else
        mData.direction = NO_DIRECTION;

    mData.speed = encodedMData & (31 << 3);

    mData.errorStatus = encodedMData & (1 << 8);
    mData.noPowerError = encodedMData & (1 << 9);
    mData.noTorqueError = encodedMData & (1 << 10);
    mData.BITError = encodedMData & (1 << 11);
    mData.overTemperatureError = encodedMData & (1 << 12);
    mData.reservedError1 = encodedMData & (1 << 13);
    mData.reservedError2 = encodedMData & (1 << 14);
    mData.unknownError = encodedMData & (1 << 15);

    return mData;
}

MotorProxy * MotorProxy_Create(void) {
    MotorProxy* me = (MotorProxy *) malloc(sizeof(MotorProxy));
    if(me!=NULL)
    {
        MotorProxy_Init(me);
    }
    return me;
}

void MotorProxy_Destroy(MotorProxy* const me) {
    if(me!=NULL)
    {
        MotorProxy_Cleanup(me);
    }
    free(me);
}
