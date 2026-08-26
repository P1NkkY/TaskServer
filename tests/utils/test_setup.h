#pragma once

#include <string>

namespace utils {

/**
 * @brief Retrieve the full name of the currently running Google Test.
 *
 * It obtains the test information via
 * ::testing::UnitTest::GetInstance()->current_test_info(). If no test is active
 * (e.g., called outside a test context), it returns "unknown_test".Otherwise,
 * it concatenates the test suite name and the test name with an underscore,
 * returning a string like "TestSuiteName_TestName".
 *
 * @return std::string
 */
std::string GetFullTestName();

}  // namespace utils