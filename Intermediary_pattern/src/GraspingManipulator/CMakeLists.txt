set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GraspingManipulator.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GraspingManipulator.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibGraspingManipulator" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibGraspingManipulator" PUBLIC ${LIBRARY_INCLUDES})

# target_link_libraries("LibGraspingManipulator" PUBLIC "LibHWProxyExamplePkg")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibGraspingManipulator"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibGraspingManipulator"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibGraspingManipulator")
endif()
