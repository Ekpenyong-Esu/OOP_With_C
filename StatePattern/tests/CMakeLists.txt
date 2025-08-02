# Unity Tests for Simplified State Pattern Implementation

# Simple State Pattern Test
add_executable("SimpleStatePatternTests" "test_simple_state_pattern.c")
target_link_libraries("SimpleStatePatternTests" PUBLIC "LibContext" 
                                                       "LibState" 
                                                       "LibMutex")
target_link_libraries("SimpleStatePatternTests" PRIVATE unity)
target_compile_definitions("SimpleStatePatternTests" PRIVATE UNITY_INCLUDE_DOUBLE)
add_test(NAME "RunSimpleStatePatternTests" COMMAND "SimpleStatePatternTests")

# Integration Tests
add_executable("IntegrationTests" "test_integration.c")
target_link_libraries("IntegrationTests" PUBLIC "LibContext" 
                                               "LibState" 
                                               "LibMutex")
target_link_libraries("IntegrationTests" PRIVATE unity)
target_compile_definitions("IntegrationTests" PRIVATE UNITY_INCLUDE_DOUBLE)
add_test(NAME "RunIntegrationTests" COMMAND "IntegrationTests")

# Mutex Tests (reuse existing)
add_executable("MutexTests" "test_mutex.c")
target_link_libraries("MutexTests" PUBLIC "LibMutex")
target_link_libraries("MutexTests" PRIVATE unity)
target_compile_definitions("MutexTests" PRIVATE UNITY_INCLUDE_DOUBLE)
add_test(NAME "RunMutexTests" COMMAND "MutexTests")


# Set warnings for test targets
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "SimpleStatePatternTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    
    target_set_warnings(
        TARGET
        "IntegrationTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    
    target_set_warnings(
        TARGET
        "MutexTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# Coverage Configuration
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
    set(COVERAGE_DEPENDENCIES 
        "SimpleStatePatternTests"
        "IntegrationTests"
        "MutexTests")

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
