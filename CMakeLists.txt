cmake_minimum_required (VERSION 3.0.0)

project (LinkedListsCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage

set(SOURCE_FILES tests/tests_main.cpp tests/linked_list_test.cpp release/linked_list.hpp)
include_directories(include tests/third_party src/)
add_executable(run_tests ${SOURCE_FILES})

if(USE_CPP14)
    set_property(TARGET run_tests PROPERTY CXX_STANDARD 14)
    message(STATUS "Enabled C++14")
elseif(USE_CPP17)
    set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
    message(STATUS "Enabled C++17")
else(USE_CPP11)
    set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)
    message(STATUS "Enabled C++11")
endif()

set_property(TARGET run_tests PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET run_tests PROPERTY CXX_EXTENSIONS OFF)

if( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( run_tests PRIVATE -Wall -Wextra -pedantic -Werror )
endif()
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( run_tests PRIVATE /W4 /WX )
endif()

if (ENABLE_COVERAGE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
    find_package(codecov)
    add_coverage(run_tests)
    list(APPEND LCOV_REMOVE_PATTERNS "/usr/")
    coverage_evaluate()
endif()

include(CTest)
add_test(NAME run_tests COMMAND $<TARGET_FILE:run_tests>)
