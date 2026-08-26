#include <gtest/gtest.h>

#include <filesystem>

#include "logger_config.h"
#include "ofstream_sink.h"
#include "ostream_sink.h"
#include "utils/test_setup.h"

using namespace common::logger;

class OstreamSinkTest : public ::testing::Test {
   protected:
    void SetUp() override {
        config_ = std::make_unique<LoggerConfig>();
        config_->WithConsole(common::logger::Severity::Info);
    }

    std::unique_ptr<LoggerConfig> config_;
};

TEST_F(OstreamSinkTest, CreateOstreamSinkShouldNotThrow) {
    EXPECT_NO_THROW(auto sink = std::make_unique<sinks::OstreamSink>(
                        config_->ConsoleConfig().value()));
}

TEST_F(OstreamSinkTest, GetOstreamSinkShouldReturnValidSink) {
    auto sink =
        std::make_unique<sinks::OstreamSink>(config_->ConsoleConfig().value());

    EXPECT_TRUE(sink->GetSink() != nullptr);
}

class OfstreamSinkTest : public ::testing::Test {
   protected:
    void SetUp() override {
        filename_ = utils::GetFullTestName() + ".log";
        config_ = std::make_unique<LoggerConfig>();
        config_->WithFile(filename_, common::logger::Severity::Info);
    }

    void TearDown() override {
        if (std::filesystem::exists(filename_)) {
            std::filesystem::remove(filename_);
        }
    }

    std::unique_ptr<LoggerConfig> config_;
    std::string filename_;
};

TEST_F(OfstreamSinkTest, CreateOfstreamSinkShouldNotThrowIfValidConfig) {
    EXPECT_NO_THROW(auto sink = std::make_unique<sinks::OfstreamSink>(
                        config_->FileConfig().value()));
}

TEST_F(OfstreamSinkTest, CreateOfstreamSinkShouldThrowIfEmptyFilename) {
    auto invalid_config = std::make_unique<LoggerConfig>();
    invalid_config->WithFile("", common::logger::Severity::Info);

    EXPECT_THROW(auto sink = std::make_unique<sinks::OfstreamSink>(
                     invalid_config->FileConfig().value()),
                 std::runtime_error);
}

TEST_F(OfstreamSinkTest, GetOfstreamSinkShouldReturnValidSink) {
    auto sink =
        std::make_unique<sinks::OfstreamSink>(config_->FileConfig().value());

    EXPECT_TRUE(sink->GetSink() != nullptr);
}