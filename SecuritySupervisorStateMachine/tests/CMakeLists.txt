add_executable("UnitTestSecuritySupervisor" "test_SecuritySupervisor.c")
target_link_libraries("UnitTestSecuritySupervisor" PUBLIC "LibSecuritySupervisor")
target_link_libraries("UnitTestSecuritySupervisor" PRIVATE gtest_main gtest)

add_test(NAME "RunUnitTestSecuritySupervisor" COMMAND "UnitTestSecuritySupervisor")

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "UnitTestSecuritySupervisor"
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
    set(COVERAGE_DEPENDENCIES "UnitTestSecuritySupervisor")

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
