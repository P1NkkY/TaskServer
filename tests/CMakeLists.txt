find_package(SOCI REQUIRED)
find_package(GTest REQUIRED)

include(GoogleTest)

cmake_policy(SET CMP0079 NEW)

file(
    GLOB_RECURSE
    TEST_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(tests ${TEST_SOURCES} utils/test_setup.h utils/test_setup.cpp)

target_include_directories(
    tests PRIVATE ${CMAKE_SOURCE_DIR}/server/common/logger_impl/sink_logger/src
)

target_link_libraries(
    tests
    PRIVATE gtest::gtest
            Boost::log
            describe
            logger_interface
            sink_logger
            database_common_interfaces
            soci_connection
            ${SOCI_LIBRARIES}
)

gtest_discover_tests(tests)
