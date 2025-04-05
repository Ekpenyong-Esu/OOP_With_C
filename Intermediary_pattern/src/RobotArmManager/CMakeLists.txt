set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/RobotArmManager.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/RobotArmManager.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibRobotArmManager" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibRobotArmManager" PUBLIC ${LIBRARY_INCLUDES})

target_link_libraries("LibRobotArmManager" PUBLIC LibRotatingArmJoint LibSlidingArmJoint LibGraspingManipulator LibAction) 

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibRobotArmManager"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibRobotArmManager"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibRobotArmManager")
endif()
