cmake_minimum_required (VERSION 3.0.0)

project (LinkedListsCPP)


set(SOURCE_FILES tests/tests_main.cpp tests/linkedListTest.cpp src/linkedList.h)
include_directories(include tests/third_party)
add_executable(RunTests ${SOURCE_FILES})

if(USE_CPP14)
    set_property(TARGET RunTests PROPERTY CXX_STANDARD 14)
    message(STATUS "Enabled C++14")
elseif(USE_CPP17)
    set_property(TARGET RunTests PROPERTY CXX_STANDARD 17)
    message(STATUS "Enabled C++17")
else(USE_CPP11)
    set_property(TARGET RunTests PROPERTY CXX_STANDARD 11)
    message(STATUS "Enabled C++11")
endif()

set_property(TARGET RunTests PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET RunTests PROPERTY CXX_EXTENSIONS OFF)

if( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( RunTests PRIVATE -Wall -Wextra -pedantic -Werror )
endif()
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( RunTests PRIVATE /W4 /WX )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
