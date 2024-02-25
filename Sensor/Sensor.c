//
// Created by mahon on 12/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "Sensor.h"

void sensor_init(Sensor* const me) {
    me->filter_freq = 0;
    me->update_freq = 0;
    me->value = 0;
    printf("%s\n",__func__ );
}

void sensor_cleanup(const Sensor* const me) {
    printf("%s\t%d\n",__func__,__LINE__);
    printf("call Sensor_Cleanup\n");
    printf("nothing to cleanup\n");
}

Sensor* sensor_create() {
    Sensor* sensor = (Sensor*) malloc(sizeof(Sensor));
    if (sensor != NULL) {
        sensor_init(sensor);
    }
    return sensor;
}

void sensor_destroy(Sensor* const sensor ) {
    if (sensor != NULL)
        sensor_cleanup(sensor);
    free(sensor);
}

/**/
int sensor_get_filter_freq(const Sensor* const me) {
    return me->filter_freq;
}

/**/
void sensor_set_filter_freq(Sensor* const me, int filter_freq) {
        me->filter_freq = filter_freq;
}

/**/
int sensor_get_update_freq(const Sensor* const me) {
    return me->update_freq;
}

/**/
void sensor_set_update_freq(Sensor* const me, int update_freq) {
        me->update_freq = update_freq;
}

/**/
int sensor_get_value(const Sensor* const me) {
    return me->value;
}

int sensor_acquire_value(Sensor* const me) {
    int const *r;
    int *w;  // read and write addressed


    switch(me->whatKindOfInterface) {
        case MEMORY_MAPPED:
            w = (int*)WRITE_ADDR;       // address to write to sensor...Note that the write address is cast to an int pointer
                                        // so that it is an address that can be dereferenced
            *w = WRITE_MASK;            //sensor command to force a read
            for (int i = 0; i < 100; ++i)
            {
                /* wait loop */
            }
            r = (int*)READ_ADDR;        // address of returned value
            me->value = *r;            // read the value in the read address and store it in the sensor object value
            break;
        case PORT_MAPPED:
            //me->value = inp(SENSOR_PORT);    // inp() is a compiler-specific port function
            me->value = SENSOR_PORT;
            break;
        default:
            printf("Invalid interface type\n");
            break;
    } // end switch
    return me->value;
}