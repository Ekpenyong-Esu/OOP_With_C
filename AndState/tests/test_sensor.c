//
// Sensor Component Tests - AND Pattern 4-Aspect Tests
// Tests the complex Sensor AND pattern with State AND Quality AND Power AND Type aspects
//

#include "unity.h"
#include "Sensor.h"

static Sensor* test_sensor;

void setUp(void) {
    test_sensor = Sensor_Create(TEMPERATURE_SENSOR, -50.0f, 150.0f);
}

void tearDown(void) {
    Sensor_Destroy(test_sensor);
    test_sensor = NULL;
}

// Test basic construction and destruction
void test_Sensor_Create_and_Destroy(void) {
    Sensor* sensor = Sensor_Create(HUMIDITY_SENSOR, 0.0f, 100.0f);
    TEST_ASSERT_NOT_NULL(sensor);
    TEST_ASSERT_EQUAL(HUMIDITY_SENSOR, sensor->type);
    Sensor_Destroy(sensor);
}

// Test initial state
void test_Sensor_Initial_State(void) {
    TEST_ASSERT_NOT_NULL(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_OFF, test_sensor->state);
    TEST_ASSERT_EQUAL(QUALITY_INVALID, test_sensor->quality);
    TEST_ASSERT_EQUAL(POWER_NORMAL, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);
    TEST_ASSERT_TRUE(test_sensor->auto_calibrate);  // Default is true in implementation
}

// Test basic sensor operations
void test_Sensor_TurnOn_TurnOff_Operations(void) {
    // Initially off
    TEST_ASSERT_EQUAL(SENSOR_OFF, test_sensor->state);

    // Turn on
    Sensor_turnOn(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);

    // Turn off
    Sensor_turnOff(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_OFF, test_sensor->state);
}

// Test calibration operations
void test_Sensor_Calibration_Operations(void) {
    Sensor_turnOn(test_sensor);

    // Calibrate - implementation briefly goes to CALIBRATING then READY
    Sensor_calibrate(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);  // Ends up in READY state

    // Take sample to move to active state
    Sensor_takeSample(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_ACTIVE, test_sensor->state);
}// Test AND Pattern: State independence
void test_Sensor_State_Independence(void) {
    DataQuality initial_quality = test_sensor->quality;
    PowerMode initial_power = test_sensor->power_mode;
    SensorType initial_type = test_sensor->type;

    // Change state without affecting other aspects
    Sensor_turnOn(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);
    TEST_ASSERT_EQUAL(initial_quality, test_sensor->quality);
    TEST_ASSERT_EQUAL(initial_power, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(initial_type, test_sensor->type);

    // Change to active state
    Sensor_takeSample(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_ACTIVE, test_sensor->state);
    TEST_ASSERT_EQUAL(initial_power, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(initial_type, test_sensor->type);
}

// Test AND Pattern: Quality independence
void test_Sensor_Quality_Independence(void) {
    SensorState initial_state = test_sensor->state;
    PowerMode initial_power = test_sensor->power_mode;
    SensorType initial_type = test_sensor->type;

    // Turn on and take sample to get quality data
    Sensor_turnOn(test_sensor);
    Sensor_takeSample(test_sensor);

    // Quality can change through sampling without affecting other aspects
    DataQuality current_quality = Sensor_getQuality(test_sensor);
    TEST_ASSERT_EQUAL(initial_power, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(initial_type, test_sensor->type);
}

// Test AND Pattern: Power independence
void test_Sensor_Power_Independence(void) {
    SensorState initial_state = test_sensor->state;
    DataQuality initial_quality = test_sensor->quality;
    SensorType initial_type = test_sensor->type;

    // Change power mode without affecting other aspects
    Sensor_setPowerMode(test_sensor, POWER_LOW);
    TEST_ASSERT_EQUAL(POWER_LOW, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(initial_state, test_sensor->state);
    TEST_ASSERT_EQUAL(initial_quality, test_sensor->quality);
    TEST_ASSERT_EQUAL(initial_type, test_sensor->type);

    Sensor_setPowerMode(test_sensor, POWER_HIGH);
    TEST_ASSERT_EQUAL(POWER_HIGH, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(initial_state, test_sensor->state);
    TEST_ASSERT_EQUAL(initial_quality, test_sensor->quality);
    TEST_ASSERT_EQUAL(initial_type, test_sensor->type);
}

// Test AND Pattern: Type independence (though type is usually fixed)
void test_Sensor_Type_Persistence(void) {
    Sensor_turnOn(test_sensor);
    Sensor_setPowerMode(test_sensor, POWER_HIGH);

    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);
}

// Test AND Pattern: All four aspects are orthogonal
void test_Sensor_Four_Aspect_Orthogonality(void) {
    // Set specific combination
    Sensor_turnOn(test_sensor);
    Sensor_setPowerMode(test_sensor, POWER_HIGH);

    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);
    TEST_ASSERT_EQUAL(POWER_HIGH, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);

    // Change only state - calibrate goes to READY state in this implementation
    Sensor_calibrate(test_sensor);
    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);         // Calibration ends in READY
    TEST_ASSERT_EQUAL(POWER_HIGH, test_sensor->power_mode);       // Unchanged
    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);     // Unchanged

    // Change only power
    Sensor_setPowerMode(test_sensor, POWER_LOW);
    TEST_ASSERT_EQUAL(SENSOR_READY, test_sensor->state);         // Unchanged
    TEST_ASSERT_EQUAL(POWER_LOW, test_sensor->power_mode);
    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);     // Unchanged
}

// Test auto-calibrate feature
void test_Sensor_AutoCalibrate_Feature(void) {
    // Initially enabled (default is true in implementation)
    TEST_ASSERT_TRUE(test_sensor->auto_calibrate);

    // Disable auto-calibrate
    Sensor_setAutoCalibrate(test_sensor, false);
    TEST_ASSERT_FALSE(test_sensor->auto_calibrate);

    // Enable auto-calibrate
    Sensor_setAutoCalibrate(test_sensor, true);
    TEST_ASSERT_TRUE(test_sensor->auto_calibrate);
}

// Test sensor data operations and value reading
void test_Sensor_Data_Operations(void) {
    Sensor_turnOn(test_sensor);

    // Get initial values - not used but kept for completeness
    float initial_value = Sensor_getValue(test_sensor);
    (void)initial_value;  // Mark as intentionally unused

    // Take sample
    bool sample_taken = Sensor_takeSample(test_sensor);
    TEST_ASSERT_TRUE(sample_taken);

    // Values should be reasonable (not testing exact values due to simulation)
    float new_value = Sensor_getValue(test_sensor);
    TEST_ASSERT_TRUE(new_value >= -50.0f && new_value <= 150.0f);  // Within range

    // Should be ready and active after sampling
    TEST_ASSERT_TRUE(Sensor_isReady(test_sensor));
    TEST_ASSERT_EQUAL(SENSOR_ACTIVE, test_sensor->state);  // Actual expected state is ACTIVE
}

// Test different sensor types
void test_Sensor_Different_Types(void) {
    Sensor* humidity_sensor = Sensor_Create(HUMIDITY_SENSOR, 0.0f, 100.0f);
    Sensor* pressure_sensor = Sensor_Create(PRESSURE_SENSOR, 0.0f, 1000.0f);
    Sensor* light_sensor = Sensor_Create(LIGHT_SENSOR, 0.0f, 10000.0f);

    TEST_ASSERT_EQUAL(HUMIDITY_SENSOR, humidity_sensor->type);
    TEST_ASSERT_EQUAL(PRESSURE_SENSOR, pressure_sensor->type);
    TEST_ASSERT_EQUAL(LIGHT_SENSOR, light_sensor->type);

    // All should start in same initial state regardless of type
    TEST_ASSERT_EQUAL(SENSOR_OFF, humidity_sensor->state);
    TEST_ASSERT_EQUAL(SENSOR_OFF, pressure_sensor->state);
    TEST_ASSERT_EQUAL(SENSOR_OFF, light_sensor->state);

    Sensor_Destroy(humidity_sensor);
    Sensor_Destroy(pressure_sensor);
    Sensor_Destroy(light_sensor);
}

// Test string helper functions
void test_Sensor_String_Helpers(void) {
    const char* state_str = Sensor_getStateString(test_sensor);
    const char* quality_str = Sensor_getQualityString(test_sensor);
    const char* power_str = Sensor_getPowerModeString(test_sensor);
    const char* type_str = Sensor_getTypeString(test_sensor);

    TEST_ASSERT_NOT_NULL(state_str);
    TEST_ASSERT_NOT_NULL(quality_str);
    TEST_ASSERT_NOT_NULL(power_str);
    TEST_ASSERT_NOT_NULL(type_str);
}


// Test statistics functions
void test_Sensor_Statistics(void) {
    Sensor_turnOn(test_sensor);

    unsigned int initial_count = Sensor_getSampleCount(test_sensor);
    TEST_ASSERT_EQUAL(0, initial_count);

    // Take a sample
    Sensor_takeSample(test_sensor);
    TEST_ASSERT_EQUAL(1, Sensor_getSampleCount(test_sensor));

    // Reset statistics
    Sensor_resetStatistics(test_sensor);
    TEST_ASSERT_EQUAL(0, Sensor_getSampleCount(test_sensor));
}

// Test threshold setting
void test_Sensor_Threshold_Setting(void) {
    // Set custom thresholds
    Sensor_setThresholds(test_sensor, 0.1f, 0.05f);

    // Should not affect other aspects
    TEST_ASSERT_EQUAL(SENSOR_OFF, test_sensor->state);
    TEST_ASSERT_EQUAL(TEMPERATURE_SENSOR, test_sensor->type);
    TEST_ASSERT_EQUAL(POWER_NORMAL, test_sensor->power_mode);
}

// Test NULL pointer safety
void test_Sensor_NULL_Safety(void) {
    // These should not crash
    Sensor_turnOn(NULL);
    Sensor_turnOff(NULL);
    Sensor_calibrate(NULL);
    Sensor_setPowerMode(NULL, POWER_NORMAL);
    Sensor_setAutoCalibrate(NULL, true);
    Sensor_takeSample(NULL);
    Sensor_displayStatus(NULL);

    // These should return safe default values
    TEST_ASSERT_FALSE(Sensor_isReady(NULL));
    TEST_ASSERT_EQUAL(0.0f, Sensor_getValue(NULL));
    TEST_ASSERT_EQUAL(QUALITY_INVALID, Sensor_getQuality(NULL));
    TEST_ASSERT_EQUAL(0, Sensor_getSampleCount(NULL));
    TEST_ASSERT_EQUAL(0.0f, Sensor_getErrorRate(NULL));
}

int main(void) {
    UNITY_BEGIN();

    // Basic functionality tests
    RUN_TEST(test_Sensor_Create_and_Destroy);
    RUN_TEST(test_Sensor_Initial_State);
    RUN_TEST(test_Sensor_TurnOn_TurnOff_Operations);
    RUN_TEST(test_Sensor_Calibration_Operations);

    // AND Pattern tests - these are the key tests!
    RUN_TEST(test_Sensor_State_Independence);
    RUN_TEST(test_Sensor_Quality_Independence);
    RUN_TEST(test_Sensor_Power_Independence);
    RUN_TEST(test_Sensor_Type_Persistence);
    RUN_TEST(test_Sensor_Four_Aspect_Orthogonality);

    // Sensor-specific functionality tests
    RUN_TEST(test_Sensor_AutoCalibrate_Feature);
    RUN_TEST(test_Sensor_Data_Operations);
    RUN_TEST(test_Sensor_Different_Types);
    RUN_TEST(test_Sensor_String_Helpers);
    RUN_TEST(test_Sensor_Statistics);
    RUN_TEST(test_Sensor_Threshold_Setting);
    RUN_TEST(test_Sensor_NULL_Safety);

    return UNITY_END();
}
