set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/QRSDetector.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/QRSDetector.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibQRSDetector" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibQRSDetector" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibQRSDetector library
target_link_libraries("LibQRSDetector" PUBLIC LibECGPkg LibTMDQueue LibTimeMarkedData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibQRSDetector"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibQRSDetector"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibQRSDetector")
endif()
