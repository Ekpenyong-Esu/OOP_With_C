set(APP_SOURCES "main.c")
set(LIBRARY_INCLUDES 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    "${CMAKE_SOURCE_DIR}/src/CRDisplay"
    "${CMAKE_SOURCE_DIR}/src/RobotArm"
    "${CMAKE_SOURCE_DIR}/src/UserInput"
    "${CMAKE_SOURCE_DIR}/src/CRRobotArmManager"
    "${CMAKE_SOURCE_DIR}/src/SafetyMonitor"
    "${CMAKE_SOURCE_DIR}/src/RealTimeTaskManager"
)

add_executable("main" ${APP_SOURCES})
target_include_directories("main" PUBLIC ${LIBRARY_INCLUDES})

target_link_libraries(
    "main"
    PUBLIC 
        CRDisplay
        RobotArm
        UserInput
        CRRobotArmManager
        SafetyMonitor
        RealTimeTaskManager
        project_options
        project_warnings
)

# Link with FreeRTOS if available
find_package(FreeRTOS)
if(FreeRTOS_FOUND)
    target_link_libraries("main" PUBLIC FreeRTOS)
endif()

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "main"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "main"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("main")
endif()
