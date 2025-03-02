/**
 * observer_pattern.c
 * Complete implementation of Observer Pattern for embedded systems
 * 
 * This example demonstrates a temperature monitoring system where:
 * - A temperature sensor acts as the Subject
 * - Multiple components (LED, Alarm, Logger) observe the temperature
 */

 #include <stdint.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include <stdio.h>
 
 /* Configuration */
 #define MAX_OBSERVERS 10
 #define LED_PIN       5
 #define ALARM_PIN     6
 #define HIGH          1
 #define LOW           0
 
 /* Forward declarations */
 typedef struct Observer Observer;
 typedef struct Subject Subject;
 
 /* Observer interface */
 struct Observer {
     void (*update)(Observer* self, void* subject, void* data);
     void* context;  /* User data for the observer */
 };
 
 /* Subject interface */
 struct Subject {
     Observer* observers[MAX_OBSERVERS];
     int observerCount;
     
     void (*attach)(Subject* self, Observer* observer);
     void (*detach)(Subject* self, Observer* observer);
     void (*notify)(Subject* self, void* data);
 };
 
 /* Subject implementation methods */
 void attachObserver(Subject* self, Observer* observer) {
     if (self->observerCount < MAX_OBSERVERS) {
         self->observers[self->observerCount++] = observer;
     }
 }
 
 void detachObserver(Subject* self, Observer* observer) {
     for (int i = 0; i < self->observerCount; i++) {
         if (self->observers[i] == observer) {
             /* Remove by shifting the array */
             for (int j = i; j < self->observerCount - 1; j++) {
                 self->observers[j] = self->observers[j + 1];
             }
             self->observerCount--;
             break;
         }
     }
 }
 
 void notifyObservers(Subject* self, void* data) {
     for (int i = 0; i < self->observerCount; i++) {
         self->observers[i]->update(self->observers[i], self, data);
     }
 }
 
 /* Initialize a generic subject */
 void subjectInit(Subject* subject) {
     subject->observerCount = 0;
     subject->attach = attachObserver;
     subject->detach = detachObserver;
     subject->notify = notifyObservers;
 }
 
 /* Temperature sensor (concrete subject) */
 typedef struct {
     Subject subject;
     float currentTemp;
     float threshold;
     bool isEnabled;
 } TempSensor;
 
 /* Initialize the temperature sensor */
 void tempSensorInit(TempSensor* sensor, float threshold) {
     subjectInit(&sensor->subject);
     sensor->currentTemp = 0.0f;
     sensor->threshold = threshold;
     sensor->isEnabled = true;
 }
 
 /* Update temperature and notify if necessary */
 void tempSensorUpdate(TempSensor* sensor, float newTemp) {
     if (!sensor->isEnabled) {
         return;
     }
     
     sensor->currentTemp = newTemp;
     
     /* Notify observers if temperature exceeds threshold */
     if (newTemp > sensor->threshold) {
         sensor->subject.notify(&sensor->subject, &sensor->currentTemp);
     }
 }
 
 /* Enable/disable the sensor */
 void tempSensorSetEnabled(TempSensor* sensor, bool enabled) {
     sensor->isEnabled = enabled;
 }
 
 /* Change the threshold */
 void tempSensorSetThreshold(TempSensor* sensor, float threshold) {
     sensor->threshold = threshold;
 }
 
 /* LED Observer */
 typedef struct {
     Observer observer;
     uint8_t pin;
     bool isBlinking;
 } LedObserver;
 
 /* Update method for the LED observer */
 void ledObserverUpdate(Observer* self, void* subject, void* data) {
     LedObserver* led = (LedObserver*)self->context;
     float temp = *(float*)data;
     
     /* Turn on LED when temperature exceeds threshold */
     if (temp > ((TempSensor*)subject)->threshold) {
         /* In a real system, we would start a timer to blink the LED */
         led->isBlinking = true;
         GPIO_SetPin(led->pin, HIGH);
         printf("LED on pin %d is now blinking (temp: %.1f°C)\n", led->pin, temp);
     }
 }
 
 /* Initialize LED observer */
 void ledObserverInit(LedObserver* led, Observer* observer, uint8_t pin) {
     observer->update = ledObserverUpdate;
     observer->context = led;
     led->pin = pin;
     led->isBlinking = false;
     GPIO_SetMode(pin, OUTPUT_MODE);
 }
 
 /* Temperature Alarm Observer */
 typedef struct {
     Observer observer;
     uint8_t pin;
     bool isActive;
 } AlarmObserver;
 
 /* Update method for the alarm observer */
 void alarmObserverUpdate(Observer* self, void* subject, void* data) {
     AlarmObserver* alarm = (AlarmObserver*)self->context;
     float temp = *(float*)data;
     
     /* Sound alarm when temperature is critical (20% above threshold) */
     if (temp > ((TempSensor*)subject)->threshold * 1.2) {
         alarm->isActive = true;
         GPIO_SetPin(alarm->pin, HIGH);
         printf("ALARM on pin %d activated! Critical temperature: %.1f°C\n", 
                alarm->pin, temp);
     }
 }
 
 /* Initialize alarm observer */
 void alarmObserverInit(AlarmObserver* alarm, Observer* observer, uint8_t pin) {
     observer->update = alarmObserverUpdate;
     observer->context = alarm;
     alarm->pin = pin;
     alarm->isActive = false;
     GPIO_SetMode(pin, OUTPUT_MODE);
 }
 
 /* Logger Observer */
 typedef struct {
     Observer observer;
     uint16_t logCount;
 } LoggerObserver;
 
 /* Update method for the logger */
 void loggerObserverUpdate(Observer* self, void* subject, void* data) {
     LoggerObserver* logger = (LoggerObserver*)self->context;
     float temp = *(float*)data;
     
     logger->logCount++;
     printf("LOG #%d: Temperature alert - Current: %.1f°C, Threshold: %.1f°C\n", 
            logger->logCount, temp, ((TempSensor*)subject)->threshold);
 }
 
 /* Initialize logger observer */
 void loggerObserverInit(LoggerObserver* logger, Observer* observer) {
     observer->update = loggerObserverUpdate;
     observer->context = logger;
     logger->logCount = 0;
 }
 
 /* Stub for GPIO functions (would be implemented by HAL in a real system) */
 void GPIO_SetPin(uint8_t pin, uint8_t state) {
     /* This would actually set hardware pins in a real system */
     /* For this example, we just simulate the action */
 }
 
 void GPIO_SetMode(uint8_t pin, uint8_t mode) {
     /* This would configure GPIO mode in a real system */
     /* For this example, we just simulate the action */
 }
 
 /* Output mode definition (would be in a HAL header in a real system) */
 #define OUTPUT_MODE 1
 
 /* Example main function showing usage */
 int main(void) {
     /* Create temperature sensor (subject) */
     TempSensor tempSensor;
     tempSensorInit(&tempSensor, 30.0f); /* Threshold at 30°C */
     
     /* Create observers */
     Observer ledObserver;
     LedObserver led;
     ledObserverInit(&led, &ledObserver, LED_PIN);
     
     Observer alarmObserver;
     AlarmObserver alarm;
     alarmObserverInit(&alarm, &alarmObserver, ALARM_PIN);
     
     Observer loggerObserver;
     LoggerObserver logger;
     loggerObserverInit(&logger, &loggerObserver);
     
     /* Register observers */
     tempSensor.subject.attach(&tempSensor.subject, &ledObserver);
     tempSensor.subject.attach(&tempSensor.subject, &alarmObserver);
     tempSensor.subject.attach(&tempSensor.subject, &loggerObserver);
     
     /* Simulate temperature changes */
     printf("Starting temperature simulation...\n");
     
     /* Normal temperature */
     tempSensorUpdate(&tempSensor, 25.0f);
     printf("Temperature updated to 25.0°C (no alerts expected)\n");
     
     /* Alert temperature */
     tempSensorUpdate(&tempSensor, 32.5f);
     
     /* Critical temperature */
     tempSensorUpdate(&tempSensor, 40.0f);
     
     /* Return to normal */
     tempSensorUpdate(&tempSensor, 28.0f);
     printf("Temperature returned to 28.0°C (below threshold)\n");
     
     /* Detach an observer */
     printf("Detaching alarm observer...\n");
     tempSensor.subject.detach(&tempSensor.subject, &alarmObserver);
     
     /* Alter the threshold */
     printf("Changing threshold to 25.0°C\n");
     tempSensorSetThreshold(&tempSensor, 25.0f);
     
     /* This should now trigger LED and logger, but not alarm */
     tempSensorUpdate(&tempSensor, 26.0f);
     
     return 0;
 }
 