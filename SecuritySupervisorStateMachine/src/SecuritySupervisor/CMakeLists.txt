set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/SecuritySupervisor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/SecuritySupervisor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibSecuritySupervisor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSecuritySupervisor" PUBLIC ${LIBRARY_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibSecuritySupervisor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibSecuritySupervisor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibSecuritySupervisor")
endif()
