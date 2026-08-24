#pragma once

#include <boost/log/sources/severity_logger.hpp>

#include "logger_interface.h"

namespace common {
namespace logger {

struct LoggerConfig;

class SinkLogger : public ILogger {
   public:
    /**
     * @brief Initializes the logging system with output destinations
     *
     * @param param Input data to create sinks with
     *
     * @note The global logging filter is not set by default, so all messages of
     * all severity levels will pass through
     * @note Does not need to set global logging filter, because we use filters
     * inside sinks
     */
    explicit SinkLogger(LoggerConfig&& config);

    bool IsEnabled(Severity severity) override;

    /**
     * @brief This function logs a message with the specified severity level
     *
     * @param level The severity level of the log message
     * @param message The actual log message text to be recorded
     *
     * This function:
     * 1) Creates a log record with the specified severity level;
     * 2) Checks if the record was successfully created;
     * 3) If valid:
     * - Attaches the record to the output stream;
     * - Writes the message to the stream;
     * - Flushes the output stream;
     * - Pushes the completed record to the logger for processing.
     */
    void Log(Severity level, std::string_view message) override;

   private:
    boost::log::sources::severity_logger_mt<Severity> logger_;
};
}  // namespace logger
}  // namespace common