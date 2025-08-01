#include <unity.h>
#include "ButtonDriver.h"
#include "Button.h"
#include "MicrowaveEmitter.h"
#include "Timer.h"

// Test fixtures
ButtonDriver* p_ButtonDriver;
Button* p_Button;
MicrowaveEmitter* p_MicrowaveEmitter;
Timer* p_Timer;

void setUp(void) {
    // Initialize components before each test
    p_ButtonDriver = ButtonDriver_Create();
    p_Button = Button_Create();
    p_MicrowaveEmitter = MicrowaveEmitter_Create();
    p_Timer = Timer_Create();

    // Set up relationships
    ButtonDriver_setItsButton(p_ButtonDriver, p_Button);
    ButtonDriver_setItsMicrowaveEmitter(p_ButtonDriver, p_MicrowaveEmitter);
    ButtonDriver_setItsTimer(p_ButtonDriver, p_Timer);
}

void tearDown(void) {
    // Clean up after each test
    ButtonDriver_Destroy(p_ButtonDriver);
    Button_Destroy(p_Button);
    MicrowaveEmitter_Destroy(p_MicrowaveEmitter);
    Timer_Destroy(p_Timer);
}

// Test component creation
void test_component_creation(void) {
    TEST_ASSERT_NOT_NULL(p_ButtonDriver);
    TEST_ASSERT_NOT_NULL(p_Button);
    TEST_ASSERT_NOT_NULL(p_MicrowaveEmitter);
    TEST_ASSERT_NOT_NULL(p_Timer);
}

// Test button state change detection
void test_button_state_change_detection(void) {
    // Initial setup
    p_ButtonDriver->oldState = 1;  // Previously pressed
    p_Button->deviceState = 0;     // Now released

    // Run event and verify toggle change
    ButtonDriver_eventReceive(p_ButtonDriver);

    // The toggle should be changed from its initial state
    // (actual assertions would depend on initial toggle state)
}

// Test relationship setup
void test_relationship_setup(void) {
    TEST_ASSERT_EQUAL_PTR(p_Button, ButtonDriver_getItsButton(p_ButtonDriver));
    TEST_ASSERT_EQUAL_PTR(p_MicrowaveEmitter, ButtonDriver_getItsMicrowaveEmitter(p_ButtonDriver));
    TEST_ASSERT_EQUAL_PTR(p_Timer, ButtonDriver_getItsTimer(p_ButtonDriver));
    TEST_ASSERT_EQUAL_PTR(p_ButtonDriver, Button_getItsButtonDriver(p_Button));
}

// Test toggle on functionality
void test_toggle_on_functionality(void) {
    // Setup for toggling ON
    p_ButtonDriver->toggleOn = 0;  // Initially OFF
    p_ButtonDriver->oldState = 1;  // Previously pressed
    p_Button->deviceState = 0;     // Now released

    // Run event
    ButtonDriver_eventReceive(p_ButtonDriver);

    // Check that toggle and backlight changed to ON
    TEST_ASSERT_EQUAL(1, p_ButtonDriver->toggleOn);
    TEST_ASSERT_EQUAL(1, p_Button->backlight);
}

// Test toggle off functionality
void test_toggle_off_functionality(void) {
    // Setup for toggling OFF
    p_ButtonDriver->toggleOn = 1;  // Initially ON
    p_ButtonDriver->oldState = 1;  // Previously pressed
    p_Button->deviceState = 0;     // Now released

    // Run event
    ButtonDriver_eventReceive(p_ButtonDriver);

    // Check that toggle and backlight changed to OFF
    TEST_ASSERT_EQUAL(0, p_ButtonDriver->toggleOn);
    TEST_ASSERT_EQUAL(0, p_Button->backlight);
}

int main(void) {
    UNITY_BEGIN();

    // Register tests
    RUN_TEST(test_component_creation);
    RUN_TEST(test_relationship_setup);
    RUN_TEST(test_button_state_change_detection);
    RUN_TEST(test_toggle_on_functionality);
    RUN_TEST(test_toggle_off_functionality);

    return UNITY_END();
}
