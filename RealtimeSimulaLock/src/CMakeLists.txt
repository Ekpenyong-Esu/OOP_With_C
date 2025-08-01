
# Add sensor modules in dependency order
add_subdirectory(OpticalSpeedSensor)    # Independent sensor module
add_subdirectory(DopplerSpeedSensors)   # Speed sensor module
add_subdirectory(GPSPositionSensors)    # Position sensor module
add_subdirectory(SensorMasterModule)    # Sensor coordinator (depends on sensor modules)
