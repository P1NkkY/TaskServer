#pragma once

#include <boost/describe.hpp>
#include <optional>
#include <string>

#include "logger_interface.h"

namespace common {
namespace logger {

/**
 * @brief Base configuration
 *
 * @note The base struct that holds the minimum severity level as a const
 * member – it is set once at construction and never changes. This guarantees
 * that the filtering threshold is fixed for the lifetime of the configuration
 * object.
 *
 */
struct SinkConfig {
    const Severity min_level_;

    explicit SinkConfig(Severity level) : min_level_(level) {}
};

/**
 * @brief File sink configuration.
 *
 */
struct FileSinkConfig : public SinkConfig {
    std::string filename_;

    explicit FileSinkConfig(const std::string& filename, Severity level)
        : SinkConfig(level), filename_(std::move(filename)) {}
};

/**
 * @brief Console sink configuration.
 *
 */
struct ConsoleSinkConfig : public SinkConfig {
    explicit ConsoleSinkConfig(Severity level) : SinkConfig(level) {}
};

/**
 * @brief Logger configuration. It allows you to specify which output sinks
 * (file, console, etc.) should be used and at what minimum severity level.
 *
 */
class LoggerConfig {
   public:
    /**
     * @brief Construct a new Logger Config object with no sinks defined.
     *
     * @note Use the WithFile() and WithConsole() methods to add config sinks.
     *
     */
    LoggerConfig() = default;
    LoggerConfig(const LoggerConfig&) = delete;
    LoggerConfig& operator=(const LoggerConfig&) = delete;
    LoggerConfig(LoggerConfig&&) = default;
    LoggerConfig& operator=(LoggerConfig&&) = default;

    /**
     * @brief Adds a file‑based logging sink to the configuration.
     *
     * @param filename Path to the log file
     * @param level Minimum severity level for messages written to this file
     *
     * @return LoggerConfig& A reference to *this to enable method chaining.
     *
     * @note Overrides previous file config when method calls multiple times.
     */
    LoggerConfig& WithFile(std::string filename,
                           Severity level = Severity::Error);

    /**
     * @brief Adds a console (standard output) logging sink to the
     * configuration.
     *
     * @param level Minimum severity level for messages printed to the console.
     *
     * @return LoggerConfig& A reference to *this to enable method chaining.
     *
     * @note Overrides previous file config when method calls multiple
     * times.
     */
    LoggerConfig& WithConsole(Severity level = Severity::Error);

    /**
     * @brief Returns an optional reference to the file‑sink configuration.
     *
     * @note Use this to inspect or read the settings after building the
     * configuration.
     *
     * @return const std::optional<FileSinkConfig>&
     */
    const std::optional<FileSinkConfig>& FileConfig() const;

    /**
     * @brief Returns an optional reference to the console‑sink configuration.
     *
     * @note Use this to inspect the console sink settings.
     *
     * @return const std::optional<ConsoleSinkConfig>&
     */
    const std::optional<ConsoleSinkConfig>& ConsoleConfig() const;

   private:
    std::optional<FileSinkConfig> file_config_;
    std::optional<ConsoleSinkConfig> console_config_;
};

}  // namespace logger
}  // namespace common