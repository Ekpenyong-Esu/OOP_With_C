set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/RotatingArmJoint.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/RotatingArmJoint.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibRotatingArmJoint" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibRotatingArmJoint" PUBLIC ${LIBRARY_INCLUDES})

# target_link_libraries("LibMotorDataPkg" INTERFACE "LibHWProxyExamplePkg")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibRotatingArmJoint"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibRotatingArmJoint"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibRotatingArmJoint")
endif()
