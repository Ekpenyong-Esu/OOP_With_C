//
// Light Component Tests - AND Pattern Basic Tests
// Tests the fundamental AND pattern with Color AND Mode aspects
//

#include "unity.h"
#include "LightPkg.h"
#include "Light.h"

static Light* test_light;

void setUp(void) {
    test_light = Light_Create();
}

void tearDown(void) {
    Light_Destroy(test_light);
    test_light = NULL;
}

// Test basic construction and destruction
void test_Light_Create_and_Destroy(void) {
    Light* light = Light_Create();
    TEST_ASSERT_NOT_NULL(light);
    Light_Destroy(light);
}

// Test initial state
void test_Light_Initial_State(void) {
    TEST_ASSERT_NOT_NULL(test_light);
    TEST_ASSERT_FALSE(Light_isOn(test_light));
    TEST_ASSERT_EQUAL(RED, Light_getColor(test_light));
    TEST_ASSERT_EQUAL(STEADY, Light_getMode(test_light));
}

// Test basic on/off operations
void test_Light_TurnOn_TurnOff(void) {
    // Initially off
    TEST_ASSERT_FALSE(Light_isOn(test_light));

    // Turn on
    Light_turnOn(test_light);
    TEST_ASSERT_TRUE(Light_isOn(test_light));

    // Turn off
    Light_turnOff(test_light);
    TEST_ASSERT_FALSE(Light_isOn(test_light));
}

// Test AND Pattern: Color independence
void test_Light_Color_Independence(void) {
    Light_turnOn(test_light);

    // Test each color
    Light_setColor(test_light, RED);
    TEST_ASSERT_EQUAL(RED, Light_getColor(test_light));
    TEST_ASSERT_TRUE(Light_isOn(test_light));  // State unchanged

    Light_setColor(test_light, YELLOW);
    TEST_ASSERT_EQUAL(YELLOW, Light_getColor(test_light));
    TEST_ASSERT_TRUE(Light_isOn(test_light));  // State unchanged

    Light_setColor(test_light, GREEN);
    TEST_ASSERT_EQUAL(GREEN, Light_getColor(test_light));
    TEST_ASSERT_TRUE(Light_isOn(test_light));  // State unchanged
}

// Test AND Pattern: Mode independence
void test_Light_Mode_Independence(void) {
    Light_turnOn(test_light);
    ColorType initial_color = Light_getColor(test_light);

    // Test each mode
    Light_setMode(test_light, STEADY);
    TEST_ASSERT_EQUAL(STEADY, Light_getMode(test_light));
    TEST_ASSERT_EQUAL(initial_color, Light_getColor(test_light));  // Color unchanged

    Light_setMode(test_light, SLOWLY);
    TEST_ASSERT_EQUAL(SLOWLY, Light_getMode(test_light));
    TEST_ASSERT_EQUAL(initial_color, Light_getColor(test_light));  // Color unchanged

    Light_setMode(test_light, QUICKLY);
    TEST_ASSERT_EQUAL(QUICKLY, Light_getMode(test_light));
    TEST_ASSERT_EQUAL(initial_color, Light_getColor(test_light));  // Color unchanged
}

// Test AND Pattern: Color and Mode are orthogonal
void test_Light_Orthogonal_Aspects(void) {
    Light_turnOn(test_light);

    // Set specific combination
    Light_setColor(test_light, YELLOW);
    Light_setMode(test_light, QUICKLY);

    TEST_ASSERT_EQUAL(YELLOW, Light_getColor(test_light));
    TEST_ASSERT_EQUAL(QUICKLY, Light_getMode(test_light));

    // Change only color
    Light_setColor(test_light, GREEN);
    TEST_ASSERT_EQUAL(GREEN, Light_getColor(test_light));
    TEST_ASSERT_EQUAL(QUICKLY, Light_getMode(test_light));  // Mode unchanged

    // Change only mode
    Light_setMode(test_light, STEADY);
    TEST_ASSERT_EQUAL(GREEN, Light_getColor(test_light));   // Color unchanged
    TEST_ASSERT_EQUAL(STEADY, Light_getMode(test_light));
}

// Test settings persist when off
void test_Light_Settings_Persist_When_Off(void) {
    Light_turnOn(test_light);
    Light_setColor(test_light, YELLOW);
    Light_setMode(test_light, SLOWLY);

    // Turn off
    Light_turnOff(test_light);
    TEST_ASSERT_FALSE(Light_isOn(test_light));

    // Settings should persist
    TEST_ASSERT_EQUAL(YELLOW, Light_getColor(test_light));
    TEST_ASSERT_EQUAL(SLOWLY, Light_getMode(test_light));

    // Turn back on - settings restored
    Light_turnOn(test_light);
    TEST_ASSERT_TRUE(Light_isOn(test_light));
    TEST_ASSERT_EQUAL(YELLOW, Light_getColor(test_light));
    TEST_ASSERT_EQUAL(SLOWLY, Light_getMode(test_light));
}

// Test NULL pointer safety
void test_Light_NULL_Safety(void) {
    // These should not crash
    Light_turnOn(NULL);
    Light_turnOff(NULL);
    Light_setColor(NULL, RED);
    Light_setMode(NULL, STEADY);
    Light_displayStatus(NULL);

    TEST_ASSERT_FALSE(Light_isOn(NULL));
    TEST_ASSERT_EQUAL(RED, Light_getColor(NULL));  // Default return
    TEST_ASSERT_EQUAL(STEADY, Light_getMode(NULL)); // Default return
}

int main(void) {
    UNITY_BEGIN();

    // Basic functionality tests
    RUN_TEST(test_Light_Create_and_Destroy);
    RUN_TEST(test_Light_Initial_State);
    RUN_TEST(test_Light_TurnOn_TurnOff);

    // AND Pattern tests - these are the key tests!
    RUN_TEST(test_Light_Color_Independence);
    RUN_TEST(test_Light_Mode_Independence);
    RUN_TEST(test_Light_Orthogonal_Aspects);

    // Additional functionality tests
    RUN_TEST(test_Light_Settings_Persist_When_Off);
    RUN_TEST(test_Light_NULL_Safety);

    return UNITY_END();
}
