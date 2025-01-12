#include <stdio.h>
#include "Sensor.h"
#include <stdlib.h>

int main() {
    // Create sensors with different interface types
    Sensor *p_Sensor0 = sensor_create(MEMORY_MAPPED);
    Sensor *p_Sensor1 = sensor_create(PORT_MAPPED);

    if (p_Sensor0 == NULL || p_Sensor1 == NULL) {
        fprintf(stderr, "Failed to create sensors\n");
        return EXIT_FAILURE;
    }

    // Set filter and update frequencies
    sensor_set_filter_freq(p_Sensor0, 50);
    sensor_set_update_freq(p_Sensor0, 100);
    sensor_set_filter_freq(p_Sensor1, 60);
    sensor_set_update_freq(p_Sensor1, 120);

    // Acquire and print sensor values
    sensor_acquire_value(p_Sensor0);
    sensor_acquire_value(p_Sensor1);

    printf("Sensor0 - Filter Frequency: %d, Update Frequency: %d, Value: %d\n",
           sensor_get_filter_freq(p_Sensor0),
           sensor_get_update_freq(p_Sensor0),
           sensor_get_value(p_Sensor0));

    printf("Sensor1 - Filter Frequency: %d, Update Frequency: %d, Value: %d\n",
           sensor_get_filter_freq(p_Sensor1),
           sensor_get_update_freq(p_Sensor1),
           sensor_get_value(p_Sensor1));

    // Clean up and destroy sensors
    sensor_destroy(p_Sensor0);
    sensor_destroy(p_Sensor1);

    return EXIT_SUCCESS;
}
