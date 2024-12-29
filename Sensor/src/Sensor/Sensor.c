//
// Created by mahon on 12/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "Sensor.h"

void sensor_init(Sensor* const self, interfaceType interface) {
    if (self == NULL) {
        return;
    }
    self->filter_freq = 0;
    self->update_freq = 0;
    self->value = 0;
    self->whatKindOfInterface = interface;
    printf("%s\t" "%d\n",__func__,__LINE__);
}

void sensor_cleanup(const Sensor* const self) {
    if (self == NULL) {
        return;
    }
    printf("%s\t%d\n",__func__,__LINE__);
    printf("call Sensor_Cleanup\n");
    printf("nothing to cleanup\n");
}

Sensor* sensor_create(interfaceType interface) {
    Sensor* sensor = (Sensor*) malloc(sizeof(Sensor));
    if (sensor != NULL) {
        sensor_init(sensor, interface);
    }
    return sensor;
}

void sensor_destroy(Sensor* const self ) {
    if (self != NULL){
        sensor_cleanup(self);
        free(self);
    }

}

/**/
int sensor_get_filter_freq(const Sensor* const self) {
    if (self == NULL) {
        return -1;
    }
    return self->filter_freq;
}

/**/
void sensor_set_filter_freq(Sensor* const self, int filter_freq) {
    if (self == NULL) {
        return;
    }
        self->filter_freq = filter_freq;
}

/**/
int sensor_get_update_freq(const Sensor* const self) {
    if (self == NULL) {
        return -1;
    }
    return self->update_freq;
}

/**/
void sensor_set_update_freq(Sensor* const self, int update_freq) {
    if (self == NULL) {
        return;
    }
        self->update_freq = update_freq;
}

/**/
int sensor_get_value(const Sensor* const self) {
    if (self == NULL) {
        return -1;
    }
    return self->value;
}

int sensor_acquire_value(Sensor* const self) {

    if (self == NULL) {
        return -1;
    }
    int *read = NULL;
    int *write = NULL;

    switch(self->whatKindOfInterface) {

        case MEMORY_MAPPED:
            write = (int*)malloc(sizeof(int));
            if (write == NULL) {
                printf("Memory allocation failed for write address\n");
                return -1;
            }
            *write = WRITE_MASK;
            for (int i = 0; i < 100; ++i) {
                /* wait loop */
            }
            read = (int*)malloc(sizeof(int));
            if (read == NULL) {
                printf("Memory allocation failed for read address\n");
                free(write);
                return -1;
            }
            *read = 1234; // Mock value for testing
            self->value = *read;
            free(write);
            free(read);
            break;
        case PORT_MAPPED:
            self->value = SENSOR_PORT;
            break;
        default:
            printf("Invalid interface type\n");
            return -1;
    }
    return 0;
}
