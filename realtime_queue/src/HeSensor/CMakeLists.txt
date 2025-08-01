set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/HeSensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/HeSensor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibHeSensor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibHeSensor" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibGasSensorBase library
target_link_libraries("LibHeSensor" PUBLIC LibGasSensorBase)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibHeSensor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibHeSensor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibHeSensor")
endif()
