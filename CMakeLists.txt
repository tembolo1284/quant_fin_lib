cmake_minimum_required(VERSION 3.15)
project(quant_fin_lib VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add option for building API
option(BUILD_API "Build REST API server" ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find required packages
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

if(BUILD_API)
    find_package(Drogon REQUIRED)
endif()

# Library sources
set(LIB_SOURCES
    src/quant_fin_lib.cpp
    src/pricing/black_scholes.cpp
    src/pricing/binomial_tree.cpp
    src/pricing/monte_carlo.cpp
    src/risk/var.cpp
    src/risk/greeks.cpp
    src/yield_curve/interpolation.cpp
    src/utils/allocators.cpp
)

# Create shared library
add_library(quant_fin_lib SHARED ${LIB_SOURCES})

# Set include directories properly for installation
target_include_directories(quant_fin_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(quant_fin_lib
    PRIVATE
        spdlog::spdlog
)

# Version the library
set_target_properties(quant_fin_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Copy shared library to Python bindings directory after build
add_custom_command(
    TARGET quant_fin_lib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/python_bindings
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:quant_fin_lib>
        ${CMAKE_SOURCE_DIR}/python_bindings/
)

# Add main executable
add_executable(quant_fin_main main.cpp)
target_link_libraries(quant_fin_main
    PRIVATE
        quant_fin_lib
)

# Add custom target to run the main executable
add_custom_target(run_main
    COMMAND quant_fin_main
    DEPENDS quant_fin_main
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# API Component
if(BUILD_API)
    # First verify config.json exists
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/api/config.json")
        message(FATAL_ERROR "api/config.json not found. Please create it first.")
    endif()

    # API sources
    set(API_SOURCES
        api/src/main.cpp
        api/src/controllers/PricingController.cpp
        api/src/filters/CorsFilter.cpp
        api/src/types/ApiTypes.cpp
    )

    # Create API executable
    add_executable(api_server ${API_SOURCES})

    target_include_directories(api_server
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/api/include
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Link API dependencies
    target_link_libraries(api_server
        PRIVATE
            quant_fin_lib
            Drogon::Drogon
            spdlog::spdlog
    )

    # Create directories and copy config at build time
    add_custom_target(api_dirs ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/logs
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/public
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/api/config.json
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json
    )
    add_dependencies(api_server api_dirs)

    # Add custom target to run the API server
    add_custom_target(run_api
        COMMAND api_server
        DEPENDS api_server
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()

# Tests
enable_testing()

# Add test executable
set(TEST_SOURCES
    test/test_quant_fin_lib.cpp
)

add_executable(test_quant_fin_lib ${TEST_SOURCES})
target_link_libraries(test_quant_fin_lib
    PRIVATE
        quant_fin_lib
        GTest::GTest
        GTest::Main
)

# Add test
add_test(
    NAME test_quant_fin_lib
    COMMAND test_quant_fin_lib
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Create a CMake configuration file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "quant_fin_lib-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Installation rules
install(TARGETS quant_fin_lib
    EXPORT quant_fin_lib-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

if(BUILD_API)
    install(TARGETS api_server
        RUNTIME DESTINATION bin
    )
    install(FILES api/config.json
        DESTINATION etc/quant_fin
    )
endif()

# Export targets for other projects to use
install(EXPORT quant_fin_lib-targets
    FILE quant_fin_lib-targets.cmake
    NAMESPACE quant_fin::
    DESTINATION lib/cmake/quant_fin_lib
)

# CMake best practice: Add uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        @ONLY
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )
endif()
