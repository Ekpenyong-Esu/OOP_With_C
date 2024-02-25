#include <stdio.h>
#include <stdlib.h>

// Forward declaration of Observer structure
struct Observer;

// Function pointer type for the update function
typedef void (*UpdateFunc)(struct Observer*);

// Subject structure
typedef struct {
    int temperature;
    int humidity;
    struct Observer** observers;
    size_t numObservers;
} WeatherStation;

// Observer structure
typedef struct Observer {
    UpdateFunc update;
} Observer;

// Function to create a new observer
struct Observer* createObserver(UpdateFunc update) {
    struct Observer* observer = (struct Observer*)malloc(sizeof(struct Observer));
    observer->update = update;
    return observer;
}

// Function to create a new weather station
WeatherStation* createWeatherStation(int initialTemperature, int initialHumidity) {
    WeatherStation* weatherStation = (WeatherStation*)malloc(sizeof(WeatherStation));
    weatherStation->temperature = initialTemperature;
    weatherStation->humidity = initialHumidity;
    weatherStation->observers = NULL;
    weatherStation->numObservers = 0;
    return weatherStation;
}

// Function to attach an observer to a weather station
void attachObserver(WeatherStation* weatherStation, struct Observer* observer) {
    weatherStation->observers = realloc(weatherStation->observers, (weatherStation->numObservers + 1) * sizeof(struct Observer*));
    weatherStation->observers[weatherStation->numObservers++] = observer;
}

// Function to notify all observers about weather changes
void notifyObservers(WeatherStation* weatherStation) {
    for (size_t i = 0; i < weatherStation->numObservers; ++i) {
        weatherStation->observers[i]->update(weatherStation->observers[i]);
    }
}

// Function to update the weather state
void updateWeather(WeatherStation* weatherStation, int newTemperature, int newHumidity) {
    weatherStation->temperature = newTemperature;
    weatherStation->humidity = newHumidity;
    notifyObservers(weatherStation);
}

// Sample update function for a temperature display
void temperatureUpdate(struct Observer* observer) {
    printf("Temperature display updated!\n");
}

// Sample update function for a humidity display
void humidityUpdate(struct Observer* observer) {
    printf("Humidity display updated!\n");
}

int main() {
    // Create a weather station and displays
    WeatherStation* weatherStation = createWeatherStation(25, 60);
    struct Observer* temperatureDisplay = createObserver(temperatureUpdate);
    struct Observer* humidityDisplay = createObserver(humidityUpdate);

    // Attach displays to the weather station
    attachObserver(weatherStation, temperatureDisplay);
    attachObserver(weatherStation, humidityDisplay);

    // Simulate weather updates
    updateWeather(weatherStation, 30, 65);

    // Clean up
    free(temperatureDisplay);
    free(humidityDisplay);
    free(weatherStation->observers);
    free(weatherStation);

    return 0;
}
