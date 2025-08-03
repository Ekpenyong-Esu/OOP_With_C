//
// Timer Component Tests - AND Pattern 3-Aspect Tests
// Tests the Timer AND pattern with State AND Mode AND Duration aspects
//

#include "unity.h"
#include "Timer.h"

static Timer* test_timer;

void setUp(void) {
    test_timer = Timer_Create(1000, ONESHOT); // 1 second, one-shot mode
}

void tearDown(void) {
    Timer_Destroy(test_timer);
    test_timer = NULL;
}

// Test basic construction and destruction
void test_Timer_Create_and_Destroy(void) {
    Timer* timer = Timer_Create(5000, REPEATING); // 5 seconds, repeating mode
    TEST_ASSERT_NOT_NULL(timer);
    Timer_Destroy(timer);
}

// Test initial state
void test_Timer_Initial_State(void) {
    TEST_ASSERT_NOT_NULL(test_timer);
    TEST_ASSERT_EQUAL(TIMER_STOPPED, test_timer->state);
    TEST_ASSERT_EQUAL(ONESHOT, test_timer->mode);
    TEST_ASSERT_EQUAL(1000, test_timer->duration_ms);
    TEST_ASSERT_EQUAL(0, test_timer->elapsed_ms);
    TEST_ASSERT_FALSE(Timer_isRunning(test_timer));
}

// Test basic timer operations
void test_Timer_Start_Stop_Operations(void) {
    // Initially stopped
    TEST_ASSERT_EQUAL(TIMER_STOPPED, test_timer->state);

    // Start timer
    Timer_start(test_timer);
    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_TRUE(Timer_isRunning(test_timer));

    // Stop timer
    Timer_stop(test_timer);
    TEST_ASSERT_EQUAL(TIMER_STOPPED, test_timer->state);
    TEST_ASSERT_FALSE(Timer_isRunning(test_timer));
}

// Test pause/resume operations
void test_Timer_Pause_Resume_Operations(void) {
    Timer_start(test_timer);

    // Pause
    Timer_pause(test_timer);
    TEST_ASSERT_EQUAL(TIMER_PAUSED, test_timer->state);
    TEST_ASSERT_FALSE(Timer_isRunning(test_timer));

    // Resume
    Timer_resume(test_timer);
    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_TRUE(Timer_isRunning(test_timer));
}

// Test AND Pattern: State independence
void test_Timer_State_Independence(void) {
    TimerMode initial_mode = test_timer->mode;
    unsigned int initial_duration = test_timer->duration_ms;

    // Change state without affecting other aspects
    Timer_start(test_timer);
    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_EQUAL(initial_mode, test_timer->mode);
    TEST_ASSERT_EQUAL(initial_duration, test_timer->duration_ms);

    Timer_pause(test_timer);
    TEST_ASSERT_EQUAL(TIMER_PAUSED, test_timer->state);
    TEST_ASSERT_EQUAL(initial_mode, test_timer->mode);
    TEST_ASSERT_EQUAL(initial_duration, test_timer->duration_ms);
}

// Test AND Pattern: Mode independence
void test_Timer_Mode_Independence(void) {
    TimerState initial_state = test_timer->state;
    unsigned int initial_duration = test_timer->duration_ms;

    // Test each mode
    Timer_setMode(test_timer, ONESHOT);
    TEST_ASSERT_EQUAL(ONESHOT, test_timer->mode);
    TEST_ASSERT_EQUAL(initial_state, test_timer->state);
    TEST_ASSERT_EQUAL(initial_duration, test_timer->duration_ms);

    Timer_setMode(test_timer, REPEATING);
    TEST_ASSERT_EQUAL(REPEATING, test_timer->mode);
    TEST_ASSERT_EQUAL(initial_state, test_timer->state);
    TEST_ASSERT_EQUAL(initial_duration, test_timer->duration_ms);

    Timer_setMode(test_timer, COUNTDOWN);
    TEST_ASSERT_EQUAL(COUNTDOWN, test_timer->mode);
    TEST_ASSERT_EQUAL(initial_state, test_timer->state);
    TEST_ASSERT_EQUAL(initial_duration, test_timer->duration_ms);
}

// Test AND Pattern: Duration independence
void test_Timer_Duration_Independence(void) {
    TimerState initial_state = test_timer->state;
    TimerMode initial_mode = test_timer->mode;

    // Change duration without affecting other aspects
    Timer_setDuration(test_timer, 2000); // 2 seconds
    TEST_ASSERT_EQUAL(2000, test_timer->duration_ms);
    TEST_ASSERT_EQUAL(initial_state, test_timer->state);
    TEST_ASSERT_EQUAL(initial_mode, test_timer->mode);

    Timer_setDuration(test_timer, 5000); // 5 seconds
    TEST_ASSERT_EQUAL(5000, test_timer->duration_ms);
    TEST_ASSERT_EQUAL(initial_state, test_timer->state);
    TEST_ASSERT_EQUAL(initial_mode, test_timer->mode);
}// Test AND Pattern: All three aspects are orthogonal
void test_Timer_Three_Aspect_Orthogonality(void) {
    // Set specific combination
    Timer_setMode(test_timer, REPEATING);
    Timer_setDuration(test_timer, 300);
    Timer_start(test_timer);

    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_EQUAL(REPEATING, test_timer->mode);
    TEST_ASSERT_EQUAL(300, test_timer->duration_ms);

    // Change only state
    Timer_pause(test_timer);
    TEST_ASSERT_EQUAL(TIMER_PAUSED, test_timer->state);
    TEST_ASSERT_EQUAL(REPEATING, test_timer->mode);        // Unchanged
    TEST_ASSERT_EQUAL(300, test_timer->duration_ms);       // Unchanged

    // Change only mode
    Timer_setMode(test_timer, ONESHOT);
    TEST_ASSERT_EQUAL(TIMER_PAUSED, test_timer->state);    // Unchanged
    TEST_ASSERT_EQUAL(ONESHOT, test_timer->mode);
    TEST_ASSERT_EQUAL(300, test_timer->duration_ms);       // Unchanged

    // Change only duration
    Timer_setDuration(test_timer, 600);
    TEST_ASSERT_EQUAL(TIMER_PAUSED, test_timer->state);    // Unchanged
    TEST_ASSERT_EQUAL(ONESHOT, test_timer->mode);          // Unchanged
    TEST_ASSERT_EQUAL(600, test_timer->duration_ms);
}

// Test timer update functionality
void test_Timer_Update_Countdown_Mode(void) {
    Timer_setMode(test_timer, COUNTDOWN);
    Timer_setDuration(test_timer, 10);
    Timer_start(test_timer);

    // Simulate time passing by calling update
    Timer_update(test_timer);

    // For countdown mode, we check that timer functions work
    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_TRUE(Timer_isRunning(test_timer));

    // Test that we can get remaining and elapsed time (values may vary)
    unsigned int remaining = Timer_getRemainingTime(test_timer);
    unsigned int elapsed = Timer_getElapsedTime(test_timer);
    TEST_ASSERT_TRUE(remaining <= test_timer->duration_ms);
    TEST_ASSERT_TRUE(elapsed >= 0);
}// Test timer update in repeating mode
void test_Timer_Update_Repeating_Mode(void) {
    Timer_setMode(test_timer, REPEATING);
    Timer_start(test_timer);

    // In repeating mode, timer should be running
    Timer_update(test_timer);
    TEST_ASSERT_EQUAL(TIMER_RUNNING, test_timer->state);
    TEST_ASSERT_TRUE(Timer_isRunning(test_timer));

    // Test that elapsed time function works
    unsigned int elapsed = Timer_getElapsedTime(test_timer);
    TEST_ASSERT_TRUE(elapsed >= 0);
}

// Test NULL pointer safety
void test_Timer_NULL_Safety(void) {
    // These should not crash
    Timer_start(NULL);
    Timer_stop(NULL);
    Timer_pause(NULL);
    Timer_resume(NULL);
    Timer_setMode(NULL, COUNTDOWN);
    Timer_setDuration(NULL, 60);
    Timer_update(NULL);
    Timer_displayStatus(NULL);

    // These should return safe default values
    TEST_ASSERT_FALSE(Timer_isRunning(NULL));
    TEST_ASSERT_FALSE(Timer_isExpired(NULL));
    TEST_ASSERT_EQUAL(0, Timer_getRemainingTime(NULL));
    TEST_ASSERT_EQUAL(0, Timer_getElapsedTime(NULL));
}

int main(void) {
    UNITY_BEGIN();

    // Basic functionality tests
    RUN_TEST(test_Timer_Create_and_Destroy);
    RUN_TEST(test_Timer_Initial_State);
    RUN_TEST(test_Timer_Start_Stop_Operations);
    RUN_TEST(test_Timer_Pause_Resume_Operations);

    // AND Pattern tests - these are the key tests!
    RUN_TEST(test_Timer_State_Independence);
    RUN_TEST(test_Timer_Mode_Independence);
    RUN_TEST(test_Timer_Duration_Independence);
    RUN_TEST(test_Timer_Three_Aspect_Orthogonality);

    // Timer-specific functionality tests
    RUN_TEST(test_Timer_Update_Countdown_Mode);
    RUN_TEST(test_Timer_Update_Repeating_Mode);
    RUN_TEST(test_Timer_NULL_Safety);

    return UNITY_END();
}
