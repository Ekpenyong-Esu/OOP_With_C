#include <gtest/gtest.h>


extern "C" {
#include "Sensor.h"
}



TEST(SensorTest, CreateSensor) {
    Sensor* sensor = sensor_create(MEMORY_MAPPED);
    ASSERT_NE(sensor, nullptr);
    sensor_destroy(sensor);
}

TEST(SensorTest, AcquireValueMemoryMapped) {
    Sensor* sensor = sensor_create(MEMORY_MAPPED);
    ASSERT_NE(sensor, nullptr);
    ASSERT_EQ(sensor_acquire_value(sensor), 0);
    ASSERT_EQ(sensor_get_value(sensor), 1234);
    sensor_destroy(sensor);
}

TEST(SensorTest, AcquireValuePortMapped) {
    Sensor* sensor = sensor_create(PORT_MAPPED);
    ASSERT_NE(sensor, nullptr);
    ASSERT_EQ(sensor_acquire_value(sensor), 0);
    ASSERT_EQ(sensor_get_value(sensor), SENSOR_PORT);
    sensor_destroy(sensor);
}

TEST(SensorTest, SetFrequencies) {
    Sensor* sensor = sensor_create(MEMORY_MAPPED);
    ASSERT_NE(sensor, nullptr);
    sensor_set_filter_freq(sensor, 50);
    sensor_set_update_freq(sensor, 100);
    ASSERT_EQ(sensor_get_filter_freq(sensor), 50);
    ASSERT_EQ(sensor_get_update_freq(sensor), 100);
    sensor_destroy(sensor);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
