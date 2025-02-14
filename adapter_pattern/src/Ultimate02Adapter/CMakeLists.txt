set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Ultimate02Adapter.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Ultimate02Adapter.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibUltimate02Adapter" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibUltimate02Adapter" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibUltimate02Adapter" PUBLIC LibUltimateO2SensorProxy Libi02Sensor)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibUltimate02Adapter"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibUltimate02Adapter"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibUltimate02Adapter")
endif()
