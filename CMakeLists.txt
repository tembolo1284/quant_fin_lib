cmake_minimum_required(VERSION 3.15)
project(quant_fin_lib VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

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
target_include_directories(quant_fin_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Copy shared library to Python bindings directory after build
add_custom_command(
    TARGET quant_fin_lib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:quant_fin_lib>
        ${CMAKE_SOURCE_DIR}/python_bindings/
)

# Add main executable
add_executable(quant_fin_main main.cpp)
target_link_libraries(quant_fin_main PRIVATE quant_fin_lib)

# Add a custom target to run the main executable
add_custom_target(run_quant_fin_main
    COMMAND quant_fin_main
    DEPENDS quant_fin_main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Enable testing
enable_testing()

# Find and link Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
set(TEST_SOURCES
    test/test_quant_fin_lib.cpp
)
add_executable(test_quant_fin_lib ${TEST_SOURCES})
target_link_libraries(test_quant_fin_lib PRIVATE quant_fin_lib GTest::GTest GTest::Main)

# Add a test target
add_test(NAME test_quant_fin_lib COMMAND test_quant_fin_lib)

# Package information
set_target_properties(quant_fin_lib PROPERTIES VERSION ${PROJECT_VERSION})

