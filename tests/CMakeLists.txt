find_package(GTest REQUIRED)
include(GoogleTest)

cmake_policy(SET CMP0079 NEW)

file(
    GLOB_RECURSE
    TEST_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(
    tests
    PRIVATE gtest::gtest
            Boost::headers
            describe
            logger_interface
            logger_impl
)

gtest_discover_tests(tests)
