add_executable("UnitTestMultireceptorIntegration" "test_MultiReceptor_Integration.c")
target_link_libraries("UnitTestMultireceptorIntegration" PUBLIC "LibMultireceptor" "LibMutex")
target_link_libraries("UnitTestMultireceptorIntegration" PRIVATE unity pthread)
target_compile_definitions("UnitTestMultireceptorIntegration" PRIVATE UNITY_INCLUDE_DOUBLE)

add_executable("UnitTestMultireceptorPerformance" "test_MultiReceptor_Performance.c")
target_link_libraries("UnitTestMultireceptorPerformance" PUBLIC "LibMultireceptor" "LibMutex")
target_link_libraries("UnitTestMultireceptorPerformance" PRIVATE unity)
target_compile_definitions("UnitTestMultireceptorPerformance" PRIVATE UNITY_INCLUDE_DOUBLE)

add_test( NAME "RunUnitTestMultireceptor" COMMAND UnitTestMultireceptor)
add_test( NAME "RunUnitTestMultireceptorIntegration" COMMAND UnitTestMultireceptorIntegration)
add_test( NAME "RunUnitTestMultireceptorPerformance" COMMAND UnitTestMultireceptorPerformance)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestMultireceptorIntegration"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    target_set_warnings(
        TARGET
        "UnitTestMultireceptorPerformance"
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
    set(COVERAGE_DEPENDENCIES "UnitTestMultireceptorIntegration" "UnitTestMultireceptorPerformance")

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
