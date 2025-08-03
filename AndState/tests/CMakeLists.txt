add_executable("UnitTestLight" "test_light.c")
target_link_libraries("UnitTestLight" PUBLIC "LibLight" "LibLightPkg")
target_link_libraries("UnitTestLight" PRIVATE unity)
add_test(NAME "RunUnitTestLight" COMMAND "UnitTestLight")

add_executable("UnitTestSensor" "test_sensor.c")
target_link_libraries("UnitTestSensor" PUBLIC "LibSensor" "LibLightPkg")
target_link_libraries("UnitTestSensor" PRIVATE unity)
add_test(NAME "RunUnitTestSensor" COMMAND "UnitTestSensor")

add_executable("UnitTestSmartLight" "test_smartlight.c")
target_link_libraries("UnitTestSmartLight" PUBLIC "LibSmartLight" "LibLightPkg" "LibSensor" "LibTimer" "LibLight")
target_link_libraries("UnitTestSmartLight" PRIVATE unity)
add_test(NAME "RunUnitTestSmartLight" COMMAND "UnitTestSmartLight")

add_executable("UnitTestTimer" "test_timer.c")
target_link_libraries("UnitTestTimer" PUBLIC "LibTimer")
target_link_libraries("UnitTestTimer" PRIVATE unity)
add_test(NAME "RunUnitTestTimer" COMMAND "UnitTestTimer")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestLight"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestSensor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestSmartLight"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestTimer"
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
    set(COVERAGE_DEPENDENCIES "UnitTestLight" "UnitTestSensor" "UnitTestSmartLight" "UnitTestTimer")

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
