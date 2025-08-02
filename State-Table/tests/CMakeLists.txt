# Simple State Table Pattern Tests (NEW - Easy to understand)
add_executable("SimpleStateTableTests" "test_simple_state_table.c")
target_link_libraries("SimpleStateTableTests" PUBLIC "LibStateTable"
                                                     "LibTokenizerStateTable")
target_link_libraries("SimpleStateTableTests" PRIVATE unity)

add_test(NAME "RunSimpleStateTableTests" COMMAND "SimpleStateTableTests")

# Simplified Comprehensive Tests (UPDATED - Clean and comprehensive)
add_executable("StateTablePatternTests" "test_state_table_pattern_simple.c")
target_link_libraries("StateTablePatternTests" PUBLIC "LibStateTable"
                                                      "LibTokenizerStateTable")
target_link_libraries("StateTablePatternTests" PRIVATE unity)

add_test(NAME "RunStateTablePatternTests" COMMAND "StateTablePatternTests")

# Basic Tokenizer Tests (UPDATED - Simplified)
add_executable("BasicTokenizerTests" "test_tokenizer_basic.c")
target_link_libraries("BasicTokenizerTests" PUBLIC "LibStateTable"
                                                  "LibTokenizerStateTable")
target_link_libraries("BasicTokenizerTests" PRIVATE unity)

add_test(NAME "RunBasicTokenizerTests" COMMAND "BasicTokenizerTests")

# Legacy tests (OLD COMPLEX VERSIONS - Commented out since they use old API)
# add_executable("StateTableTests" "test_state_table_pattern.c")
# target_link_libraries("StateTableTests" PUBLIC "LibStateTable"
#                                               "LibTokenizerStateTable"
#                                               "LibMutex")
# target_link_libraries("StateTableTests" PRIVATE unity)
# add_test(NAME "RunStateTableTests" COMMAND "StateTableTests")

# add_executable("UnitTestBuilder" "test_testbuilder.c")
# target_link_libraries("UnitTestBuilder" PUBLIC "LibTokenizeAsyncSinglePkg"
#                                               "LibTSREventQueue"
#                                               "LibTSRSyncSingleReceptor"
#                                               "LibMutex")
# target_link_libraries("UnitTestBuilder" PRIVATE unity)
# add_test(NAME "RunUnitTestBuilder" COMMAND "UnitTestBuilder")

# Set warnings for new test targets
if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "SimpleStateTableTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    
    target_set_warnings(
        TARGET
        "StateTablePatternTests"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
    
    target_set_warnings(
        TARGET
        "BasicTokenizerTests"
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
    set(COVERAGE_DEPENDENCIES "SimpleStateTableTests" "StateTablePatternTests" "BasicTokenizerTests")

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
