cmake_minimum_required(VERSION 4.0)
project(
    TaskServer
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(common)

add_executable(${PROJECT_NAME} main.cpp)

option(BUILD_TESTS "Build task server tests" ON)
option(BUILD_EXAMPLES "Build task server examples" ON)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
