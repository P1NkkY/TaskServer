#include "test_setup.h"

#include <gtest/gtest.h>

namespace utils {

std::string GetFullTestName() {
    auto* test_info = ::testing::UnitTest::GetInstance()->current_test_info();
    if (!test_info) {
        return "unknown_test";
    }

    return std::string{test_info->test_suite_name()} + "_" + test_info->name();
}

}  // namespace utils