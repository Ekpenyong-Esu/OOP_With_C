# SmartLight Component - Complex AND Pattern Demonstration

set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/SmartLight.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/SmartLight.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# Create a static library
add_library("LibSmartLight" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSmartLight" PUBLIC ${LIBRARY_INCLUDES})

# Link with all dependencies
target_link_libraries("LibSmartLight" PUBLIC 
    "LibLightPkg"
    "LibLight" 
    "LibTimer"
    "LibSensor"
)
