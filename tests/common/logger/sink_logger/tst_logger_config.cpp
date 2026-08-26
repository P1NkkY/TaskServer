#include <gtest/gtest.h>

#include "logger_config.h"

using namespace common::logger;

TEST(SinkConfigTest, SinkConfigObjectShouldStoreValidValue) {
    SinkConfig cfg(Severity::Warning);
    EXPECT_EQ(cfg.min_level_, Severity::Warning);
}

TEST(FileSinkConfigTest, FileSinkConfigObjectShouldStoreValidValues) {
    FileSinkConfig cfg("info.log", Severity::Critical);
    EXPECT_TRUE(cfg.filename_ == "info.log" &&
                cfg.min_level_ == Severity::Critical);
}

TEST(FileSinkConfigTest, FileSinkConfigCopyConstructorShouldStoreValidValues) {
    FileSinkConfig cfg("info.log", Severity::Critical);
    FileSinkConfig copy(cfg);
    EXPECT_TRUE(
        cfg.filename_ == "info.log" && cfg.min_level_ == Severity::Critical &&
        cfg.filename_ == copy.filename_ && cfg.min_level_ == copy.min_level_);
}

TEST(FileSinkConfigTest, FileSinkConfigMoveConstructorShouldStoreValidValues) {
    FileSinkConfig cfg("info.log", Severity::Critical);
    FileSinkConfig copy(std::move(cfg));
    EXPECT_TRUE(copy.filename_ == "info.log" &&
                copy.min_level_ == Severity::Critical);
}

TEST(ConsoleSinkConfigTest, ConsoleSinkConfigObjectShouldStoreValidValues) {
    ConsoleSinkConfig cfg(Severity::Critical);
    EXPECT_EQ(cfg.min_level_, Severity::Critical);
}

TEST(ConsoleSinkConfigTest,
     ConsoleSinkConfigCopyConstructorShouldStoreValidValues) {
    ConsoleSinkConfig cfg(Severity::Critical);
    ConsoleSinkConfig copy(cfg);
    EXPECT_TRUE(cfg.min_level_ == Severity::Critical &&
                cfg.min_level_ == copy.min_level_);
}

TEST(ConsoleSinkConfigTest,
     ConsoleSinkConfigMoveConstructorShouldStoreValidValues) {
    ConsoleSinkConfig cfg(Severity::Critical);
    ConsoleSinkConfig copy(std::move(cfg));
    EXPECT_TRUE(copy.min_level_ == Severity::Critical);
}

TEST(LoggerConfigTest, CreateLoggerConfigShouldStoreNulloptConfig) {
    LoggerConfig cfg;
    EXPECT_TRUE(!cfg.ConsoleConfig().has_value() &&
                !cfg.FileConfig().has_value());
}

TEST(LoggerConfigTest,
     ShouldAddFileSinkConfigToTheConfigurationAndStoreValidValues) {
    LoggerConfig cfg;
    std::string filename = "info.log";
    Severity level = Severity::Error;
    cfg.WithFile(filename, level);
    auto opt = cfg.FileConfig();

    EXPECT_TRUE(!cfg.ConsoleConfig().has_value() && opt.has_value() &&
                opt.value().filename_ == filename &&
                opt.value().min_level_ == level);
}

TEST(LoggerConfigTest,
     ShouldAddConsoleSinkConfigToTheConfigurationAndStoreValidValues) {
    LoggerConfig cfg;
    Severity level = Severity::Error;
    cfg.WithConsole(level);
    auto opt = cfg.ConsoleConfig();

    EXPECT_TRUE(!cfg.FileConfig().has_value() && opt.has_value() &&
                opt.value().min_level_ == level);
}

TEST(LoggerConfigTest, WithFileMethodShouldOverwritePreviousFileConfig) {
    LoggerConfig cfg;
    cfg.WithFile("first.log", Severity::Debug);
    cfg.WithFile("second.log", Severity::Error);
    auto opt = cfg.FileConfig();

    EXPECT_TRUE(!cfg.ConsoleConfig().has_value() && opt.has_value() &&
                opt.value().filename_ == "second.log" &&
                opt.value().min_level_ == Severity::Error);
}

TEST(LoggerConfigTest, WithFileMethodShouldOverwritePreviousConsoleConfig) {
    LoggerConfig cfg;
    cfg.WithConsole(Severity::Debug);
    cfg.WithConsole(Severity::Error);
    auto opt = cfg.ConsoleConfig();

    EXPECT_TRUE(!cfg.FileConfig().has_value() && opt.has_value() &&
                opt.value().min_level_ == Severity::Error);
}

TEST(LoggerConfigTest, ChainingWithFileAndConsolShouldStoreValidValues) {
    LoggerConfig cfg;
    std::string filename = "info.log";
    Severity level = Severity::Error;
    cfg.WithConsole(level).WithFile(filename, level);

    EXPECT_TRUE(cfg.FileConfig().has_value() &&
                cfg.ConsoleConfig().has_value() &&
                cfg.ConsoleConfig().value().min_level_ == level &&
                cfg.FileConfig().value().filename_ == filename &&
                cfg.FileConfig().value().min_level_ == level);
}

TEST(LoggerConfigTest, LoggerConfigShouldBeCorrectAfterMoving) {
    std::string filename = "move.log";
    Severity level = Severity::Critical;
    LoggerConfig original;
    original.WithFile(filename, level).WithConsole(level);
    LoggerConfig moved(std::move(original));

    auto file_config = moved.FileConfig();
    auto console_config = moved.ConsoleConfig();
    EXPECT_TRUE(file_config.has_value() && console_config.has_value() &&
                file_config.value().filename_ == filename &&
                file_config.value().min_level_ == level &&
                console_config.value().min_level_ == level);
}