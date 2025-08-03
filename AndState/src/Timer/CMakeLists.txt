# Timer Component - Time-based AND Pattern Demonstration

set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Timer.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Timer.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

# Create a static library
add_library("LibTimer" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTimer" PUBLIC ${LIBRARY_INCLUDES})

# Link with LightPkg for consistency (even though Timer doesn't use it much)
target_link_libraries("LibTimer" PUBLIC "LibLightPkg")
