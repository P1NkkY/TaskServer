#include <gtest/gtest.h>

#include <filesystem>

#include "logger_config.h"
#include "sink_logger.h"
#include "utils/test_setup.h"

using namespace common::logger;

class SinkLoggerTest : public ::testing::Test {
   protected:
    void SetUp() override {
        filename_ = utils::GetFullTestName() + ".log";

        valid_config_ = std::make_unique<LoggerConfig>();
        valid_config_->WithConsole(common::logger::Severity::Info)
            .WithFile(filename_, common::logger::Severity::Info);
    }

    void TearDown() override {
        if (std::filesystem::exists(filename_)) {
            std::filesystem::remove(filename_);
        }
    }

    std::unique_ptr<LoggerConfig> valid_config_;
    std::string filename_;
};

// TODO SinkLogger unit tests + integration tests