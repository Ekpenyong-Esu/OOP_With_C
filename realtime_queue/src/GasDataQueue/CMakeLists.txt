set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GasDataQueue.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GasDataQueue.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGasDataQueue" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGasDataQueue" PUBLIC ${LIBRARY_INCLUDES})

# Link with LibGasData
target_link_libraries("LibGasDataQueue" PUBLIC LibGasData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGasDataQueue"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGasDataQueue"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGasDataQueue")
endif()
