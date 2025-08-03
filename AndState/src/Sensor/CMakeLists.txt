# Sensor Component - Multi-aspect AND Pattern Demonstration

set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Sensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Sensor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# Create a static library
add_library("LibSensor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSensor" PUBLIC ${LIBRARY_INCLUDES})

# Link with LightPkg for consistency
target_link_libraries("LibSensor" PUBLIC "LibLightPkg")
