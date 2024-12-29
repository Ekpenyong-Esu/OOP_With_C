//
// Created by mahon on 12/10/2023.
//

#ifndef OOP_WITH_C_SENSOR_H
#define OOP_WITH_C_SENSOR_H

/* Class sensor */

#define WRITE_ADDR  0x1111
#define WRITE_MASK  0x2222
#define READ_ADDR   0x3333
#define SENSOR_PORT 0x4444

// interfaceType is an enumeration type
typedef enum interfaceType
{
    MEMORY_MAPPED,
    PORT_MAPPED,
    MAPPED_MAX
} interfaceType;


typedef struct Sensor Sensor;  // forward declaration of the Sensor struct

// Sensor class definition
struct Sensor {
    int filter_freq;
    int update_freq;
    int value;
    interfaceType whatKindOfInterface;
};

// Sensor class member functions
Sensor* sensor_create(interfaceType interface);   // constructor to create a new Sensor object

void sensor_destroy(Sensor* const self);  // destructor to destroy a Sensor object

int  sensor_get_filter_freq(const Sensor* const self); // getter to get the filter frequency
void sensor_set_filter_freq(Sensor* const self, int filter_freq);  // setter to set the filter frequency
int  sensor_get_update_freq(const Sensor* const self);            // getter to get the update frequency
void sensor_set_update_freq(Sensor* const self, int update_freq);  // setter to set the update frequency
int  sensor_get_value(const Sensor* const self);                 // getter to get the sensor value
int sensor_acquire_value(Sensor* const self);                    // acquire the sensor value

#endif //OOP_WITH_C_SENSOR_H
