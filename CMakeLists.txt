cmake_minimum_required(VERSION 3.22)
project(osc++ VERSION 2.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)

option(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

option(BUILD_TESTS "Build tests" ON)
set(GOOGLE_TEST_DIR "" CACHE PATH "Path to GoogleTest source")

if(BUILD_TESTS)
    enable_testing()

    if(GOOGLE_TEST_DIR)
        add_subdirectory(${GOOGLE_TEST_DIR} googletest)
    else()
        find_package(GTest REQUIRED)
    endif()

    add_subdirectory(test)
endif()
