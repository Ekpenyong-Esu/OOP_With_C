//
// SmartLight Component Tests - Advanced AND Pattern Integration Tests
// Tests the complex SmartLight that combines multiple AND patterns
//

#include "unity.h"
#include "SmartLight.h"
#include <string.h>

static SmartLight* test_smart_light;

void setUp(void) {
    test_smart_light = SmartLight_Create();
}

void tearDown(void) {
    SmartLight_Destroy(test_smart_light);
    test_smart_light = NULL;
}

// Test basic construction and destruction
void test_SmartLight_Create_and_Destroy(void) {
    SmartLight* smart_light = SmartLight_Create();
    TEST_ASSERT_NOT_NULL(smart_light);
    SmartLight_Destroy(smart_light);
}

// Test initial state
void test_SmartLight_Initial_State(void) {
    TEST_ASSERT_NOT_NULL(test_smart_light);

    // Light aspects - test what's available
    TEST_ASSERT_FALSE(SmartLight_isOn(test_smart_light));

    // SmartLight specific - using actual enums and functions
    TEST_ASSERT_EQUAL(AUTO_MODE, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_EQUAL(BRIGHTNESS_MEDIUM, SmartLight_getBrightness(test_smart_light));
    TEST_ASSERT_EQUAL(0, SmartLight_getManualOverrides(test_smart_light));
}

// Test basic light operations
void test_SmartLight_Basic_Light_Operations(void) {
    // Initially off
    TEST_ASSERT_FALSE(SmartLight_isOn(test_smart_light));

    // Turn on
    SmartLight_turnOn(test_smart_light);
    TEST_ASSERT_TRUE(SmartLight_isOn(test_smart_light));

    // Turn off
    SmartLight_turnOff(test_smart_light);
    TEST_ASSERT_FALSE(SmartLight_isOn(test_smart_light));
}

// Test AND Pattern: Light aspect independence
void test_SmartLight_Light_Aspect_Independence(void) {
    SmartMode initial_mode = SmartLight_getMode(test_smart_light);
    BrightnessLevel initial_brightness = SmartLight_getBrightness(test_smart_light);

    // Change light properties without affecting other aspects
    SmartLight_turnOn(test_smart_light);
    SmartLight_setColor(test_smart_light, YELLOW);
    SmartLight_setFlashMode(test_smart_light, QUICKLY);

    TEST_ASSERT_TRUE(SmartLight_isOn(test_smart_light));

    // Other aspects should be unchanged
    TEST_ASSERT_EQUAL(initial_mode, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_EQUAL(initial_brightness, SmartLight_getBrightness(test_smart_light));
}

// Test AND Pattern: Mode aspect independence
void test_SmartLight_Mode_Aspect_Independence(void) {
    bool initial_light_on = SmartLight_isOn(test_smart_light);
    BrightnessLevel initial_brightness = SmartLight_getBrightness(test_smart_light);

    // Change smart mode without affecting other aspects
    SmartLight_setMode(test_smart_light, MANUAL_MODE);

    TEST_ASSERT_EQUAL(MANUAL_MODE, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_EQUAL(initial_light_on, SmartLight_isOn(test_smart_light));
    TEST_ASSERT_EQUAL(initial_brightness, SmartLight_getBrightness(test_smart_light));
}

// Test AND Pattern: Brightness aspect independence
void test_SmartLight_Brightness_Aspect_Independence(void) {
    bool initial_light_on = SmartLight_isOn(test_smart_light);
    SmartMode initial_mode = SmartLight_getMode(test_smart_light);

    // Change brightness without affecting other aspects
    SmartLight_setBrightness(test_smart_light, BRIGHTNESS_BRIGHT);

    TEST_ASSERT_EQUAL(BRIGHTNESS_BRIGHT, SmartLight_getBrightness(test_smart_light));
    TEST_ASSERT_EQUAL(initial_light_on, SmartLight_isOn(test_smart_light));
    TEST_ASSERT_EQUAL(initial_mode, SmartLight_getMode(test_smart_light));
}

// Test AND Pattern: All aspects are orthogonal
void test_SmartLight_Complete_Orthogonality(void) {
    // Set specific combination across all aspects
    SmartLight_turnOn(test_smart_light);
    SmartLight_setColor(test_smart_light, GREEN);
    SmartLight_setFlashMode(test_smart_light, SLOWLY);
    SmartLight_setMode(test_smart_light, ADAPTIVE_MODE);
    SmartLight_setBrightness(test_smart_light, BRIGHTNESS_BRIGHT);

    // Verify all aspects are set correctly
    TEST_ASSERT_TRUE(SmartLight_isOn(test_smart_light));
    TEST_ASSERT_EQUAL(ADAPTIVE_MODE, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_EQUAL(BRIGHTNESS_BRIGHT, SmartLight_getBrightness(test_smart_light));

    // Change only one aspect at a time and verify others remain unchanged

    // Change only mode
    SmartLight_setMode(test_smart_light, TIMER_MODE);
    TEST_ASSERT_EQUAL(TIMER_MODE, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_TRUE(SmartLight_isOn(test_smart_light));                      // Unchanged
    TEST_ASSERT_EQUAL(BRIGHTNESS_BRIGHT, SmartLight_getBrightness(test_smart_light)); // Unchanged
}

// Test feature control functions
void test_SmartLight_Feature_Control(void) {
    // Test motion detection control
    SmartLight_enableMotionDetection(test_smart_light, false);
    SmartLight_enableMotionDetection(test_smart_light, true);

    // Test auto dimming control
    SmartLight_enableAutoDimming(test_smart_light, false);
    SmartLight_enableAutoDimming(test_smart_light, true);

    // Test energy saving control
    SmartLight_enableEnergySaving(test_smart_light, true);
    SmartLight_enableEnergySaving(test_smart_light, false);

    // These should not crash or affect basic light state
    TEST_ASSERT_FALSE(SmartLight_isOn(test_smart_light));
    TEST_ASSERT_EQUAL(AUTO_MODE, SmartLight_getMode(test_smart_light));
}

// Test configuration functions
void test_SmartLight_Configuration(void) {
    // Test light threshold setting
    SmartLight_setLightThreshold(test_smart_light, 200.0f);

    // Test fade duration setting
    SmartLight_setFadeDuration(test_smart_light, 2000);

    // Test auto timeout setting
    SmartLight_setAutoTimeout(test_smart_light, 600000);

    // These should not affect basic state
    TEST_ASSERT_FALSE(SmartLight_isOn(test_smart_light));
    TEST_ASSERT_EQUAL(AUTO_MODE, SmartLight_getMode(test_smart_light));
    TEST_ASSERT_EQUAL(BRIGHTNESS_MEDIUM, SmartLight_getBrightness(test_smart_light));
}

// Test smart operations
void test_SmartLight_Smart_Operations(void) {
    // Test update function
    SmartLight_update(test_smart_light);

    // Test fade to level
    SmartLight_fadeToLevel(test_smart_light, BRIGHTNESS_DIM);
    TEST_ASSERT_EQUAL(BRIGHTNESS_DIM, SmartLight_getBrightness(test_smart_light));

    // Test respond to motion (should not crash)
    SmartLight_respondToMotion(test_smart_light);

    // Test adjust to ambient light (should not crash)
    SmartLight_adjustToAmbientLight(test_smart_light);

    // Basic state should be maintained
    TEST_ASSERT_NOT_NULL(test_smart_light);
}

// Test statistics functions
void test_SmartLight_Statistics(void) {
    unsigned int initial_overrides = SmartLight_getManualOverrides(test_smart_light);

    // Manual color change should increment override count
    SmartLight_setColor(test_smart_light, GREEN);
    TEST_ASSERT_EQUAL(initial_overrides + 1, SmartLight_getManualOverrides(test_smart_light));

    // Reset statistics
    SmartLight_resetStatistics(test_smart_light);
    TEST_ASSERT_EQUAL(0, SmartLight_getManualOverrides(test_smart_light));

    // Test learning function (should not crash)
    SmartLight_learnFromUsage(test_smart_light);
}

// Test string conversion helpers
void test_SmartLight_String_Helpers(void) {
    const char* mode_str = SmartLight_getModeString(test_smart_light);
    const char* brightness_str = SmartLight_getBrightnessString(test_smart_light);

    TEST_ASSERT_NOT_NULL(mode_str);
    TEST_ASSERT_NOT_NULL(brightness_str);

    // Should return reasonable strings
    TEST_ASSERT_TRUE(strlen(mode_str) > 0);
    TEST_ASSERT_TRUE(strlen(brightness_str) > 0);
}

// Test NULL pointer safety
void test_SmartLight_NULL_Safety(void) {
    // These should not crash
    SmartLight_turnOn(NULL);
    SmartLight_turnOff(NULL);
    SmartLight_toggle(NULL);
    SmartLight_setMode(NULL, MANUAL_MODE);
    SmartLight_setBrightness(NULL, BRIGHTNESS_MAX);
    SmartLight_setColor(NULL, RED);
    SmartLight_setFlashMode(NULL, STEADY);
    SmartLight_update(NULL);
    SmartLight_displayStatus(NULL);

    // These should return safe default values
    TEST_ASSERT_FALSE(SmartLight_isOn(NULL));
    TEST_ASSERT_EQUAL(MANUAL_MODE, SmartLight_getMode(NULL));
    TEST_ASSERT_EQUAL(BRIGHTNESS_OFF, SmartLight_getBrightness(NULL));
    TEST_ASSERT_EQUAL(0, SmartLight_getManualOverrides(NULL));

    // String helpers return "NULL" string for NULL pointer
    TEST_ASSERT_EQUAL_STRING("NULL", SmartLight_getModeString(NULL));
    TEST_ASSERT_EQUAL_STRING("NULL", SmartLight_getBrightnessString(NULL));
}

int main(void) {
    UNITY_BEGIN();

    // Basic functionality tests
    RUN_TEST(test_SmartLight_Create_and_Destroy);
    RUN_TEST(test_SmartLight_Initial_State);
    RUN_TEST(test_SmartLight_Basic_Light_Operations);

    // AND Pattern tests - these are the key tests!
    RUN_TEST(test_SmartLight_Light_Aspect_Independence);
    RUN_TEST(test_SmartLight_Mode_Aspect_Independence);
    RUN_TEST(test_SmartLight_Brightness_Aspect_Independence);
    RUN_TEST(test_SmartLight_Complete_Orthogonality);

    // SmartLight-specific functionality tests
    RUN_TEST(test_SmartLight_Feature_Control);
    RUN_TEST(test_SmartLight_Configuration);
    RUN_TEST(test_SmartLight_Smart_Operations);
    RUN_TEST(test_SmartLight_Statistics);
    RUN_TEST(test_SmartLight_String_Helpers);
    RUN_TEST(test_SmartLight_NULL_Safety);

    return UNITY_END();
}
