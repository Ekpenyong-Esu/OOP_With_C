set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Acme02SensorProxy.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Acme02SensorProxy.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibAcmeO2SensorProxy" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibAcmeO2SensorProxy" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
# target_link_libraries("LibAcmeO2SensorProxy" PUBLIC )


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibAcmeO2SensorProxy"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibAcmeO2SensorProxy"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibAcmeO2SensorProxy")
endif()
