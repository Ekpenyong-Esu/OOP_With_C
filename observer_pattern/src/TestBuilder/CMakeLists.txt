set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TestBuilder.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TestBuilder.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibTestBuilder" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibTestBuilder" PUBLIC ${LIBRARY_INCLUDES})

# link the LibECGPkg library to the LibTestBuilder library
target_link_libraries("LibTestBuilder" PUBLIC
    LibECGPkg
    LibTMDQueue
    LibWaveFormDisplay
    LibTimeMarkedData
    LibHistogramDisplay
    LibQRSDetector
    LibArrhythmiaDetector
    LibECG_Module
    LibNotificationHandle
)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibTestBuilder"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibTestBuilder"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibTestBuilder")
endif()
