//
// Comprehensive AND Pattern Demonstration
// Shows all components working together to demonstrate
// different aspects of the AND pattern
//

#include "Light.h"
#include "Timer.h"
#include "Sensor.h"
#include "SmartLight.h"
#include <stdio.h>
#include <unistd.h>  // For sleep

// Function to simulate passage of time
void simulate_time_passage(int seconds) {
    printf("\n--- Simulating %d seconds passing ---\n", seconds);
    for (int i = 0; i < seconds; i++) {
        sleep(1);  // Wait 1 second
        printf(".");
        fflush(stdout);
    }
    printf("\n");
}

void demonstrate_basic_light_and_pattern(void) {
    printf("\n=== 1. Basic Light AND Pattern ===\n");

    Light* light = Light_Create();
    if (!light) return;

    printf("\nDemonstrating independent aspects (Color AND Mode):\n");
    Light_turnOn(light);

    // Show that color and mode are independent (AND pattern)
    Light_setColor(light, RED);
    Light_setMode(light, STEADY);
    Light_displayStatus(light);

    Light_setColor(light, YELLOW);  // Change color only
    Light_displayStatus(light);

    Light_setMode(light, QUICKLY);  // Change mode only
    Light_displayStatus(light);

    Light_setColor(light, GREEN);   // Change color again
    Light_setMode(light, SLOWLY);   // Change mode again
    Light_displayStatus(light);

    printf("\nKey insight: Color and Mode are orthogonal (independent)!\n");

    Light_Destroy(light);
}

void demonstrate_timer_and_pattern(void) {
    printf("\n=== 2. Timer AND Pattern ===\n");

    Timer* timer = Timer_Create(3000, REPEATING);  // 3 second repeating timer
    if (!timer) return;

    printf("\nDemonstrating Timer AND aspects (State AND Mode AND Duration):\n");

    // Show independent aspects
    Timer_setMode(timer, ONESHOT);
    Timer_setDuration(timer, 2000);
    Timer_setRepeatCount(timer, 3);
    Timer_displayStatus(timer);

    Timer_start(timer);

    // Monitor timer for several updates
    for (int i = 0; i < 8; i++) {
        Timer_update(timer);
        Timer_displayStatus(timer);
        simulate_time_passage(1);

        if (Timer_isExpired(timer)) {
            printf("Timer expired! Restarting with different mode...\n");
            Timer_setMode(timer, REPEATING);
            Timer_start(timer);
        }
    }

    printf("\nKey insight: Timer state, mode, and duration are independent!\n");

    Timer_Destroy(timer);
}

void demonstrate_sensor_and_pattern(void) {
    printf("\n=== 3. Sensor AND Pattern ===\n");

    Sensor* temp_sensor = Sensor_Create(TEMPERATURE_SENSOR, -10.0f, 50.0f);
    if (!temp_sensor) return;

    printf("\nDemonstrating Sensor AND aspects (State AND Quality AND Power):\n");

    Sensor_turnOn(temp_sensor);
    Sensor_displayStatus(temp_sensor);

    // Show independent aspects
    Sensor_setPowerMode(temp_sensor, POWER_LOW);
    Sensor_displayStatus(temp_sensor);

    // Take some samples while showing aspects change independently
    for (int i = 0; i < 5; i++) {
        Sensor_takeSample(temp_sensor);

        // Change power mode mid-sampling
        if (i == 2) {
            Sensor_setPowerMode(temp_sensor, POWER_HIGH);
            printf("Switched to high power mode during sampling\n");
        }

        Sensor_displayStatus(temp_sensor);
        simulate_time_passage(1);
    }

    printf("\nKey insight: Sensor state, quality, and power mode are independent!\n");

    Sensor_Destroy(temp_sensor);
}

void demonstrate_smartlight_complex_and_pattern(void) {
    printf("\n=== 4. SmartLight Complex AND Pattern ===\n");

    SmartLight* smart = SmartLight_Create();
    if (!smart) return;

    printf("\nDemonstrating SmartLight multiple AND aspects:\n");
    printf("- Light state (Color AND Mode)\n");
    printf("- Smart mode (Manual/Auto/Timer/Adaptive)\n");
    printf("- Brightness level\n");
    printf("- Feature flags (Motion/AutoDim/EnergySave)\n");
    printf("- Sensor inputs\n");
    printf("- Timer behaviors\n");

    SmartLight_displayStatus(smart);

    printf("\n--- Testing independent aspect changes ---\n");

    // Change mode without affecting other aspects
    SmartLight_setMode(smart, MANUAL_MODE);
    SmartLight_displayStatus(smart);

    // Change brightness without affecting mode
    SmartLight_setBrightness(smart, BRIGHTNESS_BRIGHT);
    SmartLight_displayStatus(smart);

    // Enable features without affecting brightness or mode
    SmartLight_enableEnergySaving(smart, true);
    SmartLight_enableMotionDetection(smart, true);
    SmartLight_displayStatus(smart);

    // Change to auto mode and let it run
    SmartLight_setMode(smart, AUTO_MODE);
    SmartLight_turnOn(smart);

    printf("\n--- Running smart behavior simulation ---\n");
    for (int i = 0; i < 5; i++) {
        SmartLight_update(smart);
        simulate_time_passage(1);
    }

    SmartLight_displayStatus(smart);

    printf("\nKey insight: ALL aspects are independent AND work together!\n");

    SmartLight_Destroy(smart);
}

void demonstrate_and_pattern_principles(void) {
    printf("\n=== 5. AND Pattern Principles Summary ===\n");

    printf("\nThe AND Pattern demonstrates:\n");
    printf("1. INDEPENDENCE: Change one aspect without affecting others\n");
    printf("2. CONCURRENCY: Multiple aspects active simultaneously\n");
    printf("3. COMPOSITION: Complex behavior from simple aspects\n");
    printf("4. ORTHOGONALITY: Aspects don't interfere with each other\n");

    printf("\nExamples we've seen:\n");
    printf("• Light: Color AND Flash Mode\n");
    printf("• Timer: State AND Mode AND Duration\n");
    printf("• Sensor: Operational State AND Data Quality AND Power Mode\n");
    printf("• SmartLight: ALL of the above PLUS Smart Mode AND Brightness AND Features\n");

    printf("\nReal-world applications:\n");
    printf("• Car: Speed AND Direction AND Gear AND Headlights AND Radio\n");
    printf("• Phone: Network AND Battery AND Screen AND Apps AND Bluetooth\n");
    printf("• Game Character: Health AND Position AND Animation AND Inventory\n");

    printf("\nWhy this matters:\n");
    printf("• Easier to understand (simple parts)\n");
    printf("• Easier to test (test aspects independently)\n");
    printf("• Easier to maintain (change one thing at a time)\n");
    printf("• More flexible (combine aspects in new ways)\n");
}

int main() {
    printf("=== Comprehensive AND Pattern Demonstration ===\n");
    printf("This demo shows how the AND Pattern works at different levels\n");

    demonstrate_basic_light_and_pattern();
    demonstrate_timer_and_pattern();
    demonstrate_sensor_and_pattern();
    demonstrate_smartlight_complex_and_pattern();
    demonstrate_and_pattern_principles();

    printf("\n=== Demo Complete ===\n");
    printf("You've seen the AND Pattern from simple to complex!\n");
    printf("Start with simple examples, then build complexity.\n");

    return 0;
}
