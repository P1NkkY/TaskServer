#include <gtest/gtest.h>

#include <filesystem>

#include "logger_config.h"
#include "sink_factory.h"
#include "utils/test_setup.h"

using namespace common::logger;

class FactoryTest : public ::testing::Test {
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

TEST_F(FactoryTest, CreateOstreamFactoryShouldNotThrow) {
    EXPECT_NO_THROW(
        sinks::OstreamFactory factory(*valid_config_->ConsoleConfig()));
}

TEST_F(FactoryTest, CreateOstreamSinkShouldReturnValidPointer) {
    sinks::OstreamFactory factory(*valid_config_->ConsoleConfig());

    auto sink = factory.CreateSink();

    EXPECT_NE(sink->GetSink(), nullptr);
}

TEST_F(FactoryTest, CreateOfstreamFactoryShouldNotThrow) {
    EXPECT_NO_THROW(
        sinks::OfstreamFactory factory(*valid_config_->FileConfig()));
}

TEST_F(FactoryTest, CreateOfstreamSinkShouldReturnValidPointer) {
    sinks::OfstreamFactory factory(*valid_config_->FileConfig());

    auto sink = factory.CreateSink();

    EXPECT_NE(sink->GetSink(), nullptr);
}