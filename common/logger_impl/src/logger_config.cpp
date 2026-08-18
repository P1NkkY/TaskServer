#include "logger_config.h"

namespace common::logger {

LoggerConfig& LoggerConfig::WithFile(std::string filename, Severity level) {
    file_config_.emplace(std::move(filename), level);
    return *this;
}

LoggerConfig& LoggerConfig::WithConsole(Severity level) {
    console_config_.emplace(level);
    return *this;
}

const std::optional<FileSinkConfig>& LoggerConfig::FileConfig() const {
    return file_config_;
}

const std::optional<ConsoleSinkConfig>& LoggerConfig::ConsoleConfig() const {
    return console_config_;
}

}  // namespace common::logger