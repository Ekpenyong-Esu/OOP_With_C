# set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Led.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/RobotInterruptVectorTable.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibRobotInterruptVectorTable" INTERFACE)
target_include_directories("LibRobotInterruptVectorTable" INTERFACE ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
target_link_libraries("LibRobotInterruptVectorTable" INTERFACE LibButtonHandler)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibRobotInterruptVectorTable"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibRobotInterruptVectorTable"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibRobotInterruptVectorTable")
endif()
