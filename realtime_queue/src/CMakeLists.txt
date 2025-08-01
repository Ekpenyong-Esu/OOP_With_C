# Add subdirectories in dependency order
add_subdirectory(GasSensorBase)  # Base first as others depend on it
add_subdirectory(GasData)        # Basic data structures
add_subdirectory(GasDataQueue)   # Queue depends on GasData
add_subdirectory(O2Sensor)       # Sensors depend on base
add_subdirectory(N2Sensor)
add_subdirectory(HeSensor)
add_subdirectory(GasDisplay)     # Display depends on GasData
add_subdirectory(GasController)  # Controller depends on GasData and Display
add_subdirectory(SensorThread)   # Thread depends on all sensors and queue
