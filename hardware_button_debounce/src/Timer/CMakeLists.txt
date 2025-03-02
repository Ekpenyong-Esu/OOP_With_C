set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Timer.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Timer.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTimer" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTimer" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
# target_link_libraries("LibTimer" PUBLIC Libi02Sensor LibAcmeO2SensorProxy)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTimer"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTimer"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTimer")
endif()
