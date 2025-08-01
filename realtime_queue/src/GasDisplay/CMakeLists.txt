set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasDisplay.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasDisplay.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasDisplay" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasDisplay" PUBLIC ${LIBRARY_INCLUDES})

# Link required libraries
target_link_libraries("LibGasDisplay" PUBLIC LibGasData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasDisplay"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasDisplay"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasDisplay")
endif()
