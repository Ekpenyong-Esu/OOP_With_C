add_executable("UnitTestCircle" "test_circle.c")
target_link_libraries("UnitTestCircle" PUBLIC "LibCircle")
target_link_libraries("UnitTestCircle" PRIVATE unity)

add_executable("UnitTestRectangle" "test_rectangle.c")
target_link_libraries("UnitTestRectangle" PUBLIC "LibRectangle")
target_link_libraries("UnitTestRectangle" PRIVATE unity)

add_executable("UnitTestFactoryShape" "test_factory_shape.c")
target_link_libraries("UnitTestFactoryShape" PUBLIC "LibShapeFactory")
target_link_libraries("UnitTestFactoryShape" PRIVATE unity)

add_executable("UnitTestTriangle" "test_triangle.c")
target_link_libraries("UnitTestTriangle" PUBLIC "LibTriangle")
target_link_libraries("UnitTestTriangle" PRIVATE unity)


add_test(NAME "RunUnitTestCircle" COMMAND "UnitTestCircle")
add_test(NAME "RunUnitTestFactoryShape" COMMAND "UnitTestFactoryShape")
add_test(NAME "RunUnitTestRectangle" COMMAND "UnitTestRectangle")
add_test(NAME "RunUnitTestTriangle" COMMAND "UnitTestTriangle")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestCircle"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestFactoryShape"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestRectangle"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestTriangle"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(ENABLE_COVERAGE)
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${PROJECT_SOURCE_DIR}/app/*"
        "${PROJECT_SOURCE_DIR}/cmake/*"
        "${PROJECT_SOURCE_DIR}/docs/*"
        "${PROJECT_SOURCE_DIR}/external/*"
        "${PROJECT_SOURCE_DIR}/tests/*"
        "${PROJECT_SOURCE_DIR}/build/*"
        "/usr/include/*")
    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES "UnitTestCircle" "UnitTestFactoryShape" "UnitTestRectangle" "UnitTestTriangle")

    setup_target_for_coverage_gcovr_html(
        NAME
        ${COVERAGE_MAIN}
        EXECUTABLE
        ctest
        DEPENDENCIES
        ${COVERAGE_DEPENDENCIES}
        BASE_DIRECTORY
        ${CMAKE_SOURCE_DIR})
endif()

