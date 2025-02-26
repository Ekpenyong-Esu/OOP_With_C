set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Acme02Adapter.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Acme02Adapter.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibAcme02Adapter" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibAcme02Adapter" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibAcme02Adapter" PUBLIC Libi02Sensor LibAcmeO2SensorProxy)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibAcme02Adapter"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibAcme02Adapter"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibAcme02Adapter")
endif()
