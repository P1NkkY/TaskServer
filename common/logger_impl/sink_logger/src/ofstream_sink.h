#pragma once

#include "logger_config.h"
#include "sink_interface.h"

namespace common {
namespace logger {
namespace sinks {

/**
 * @brief File-based logging sink. This sink writes log records to a file using
 * Boost.Log text_ostream_backend. It is configured via FileSinkConfig.
 *
 * @note The sink initializes itself in the constructor.
 */
class OfstreamSink : public ISink {
   public:
    /**
     * @brief Constructs the file sink and immediately initializes it.
     *
     * @param config Configuration for the file sink
     *
     * @throws std::runtime_error If filename is empty or file cannot be opened.
     */
    explicit OfstreamSink(FileSinkConfig config);

    /**
     * @brief Returns the sink object.
     *
     * @return boost::shared_ptr<boost::log::sinks::sink>
     */
    boost::shared_ptr<boost::log::sinks::sink> GetSink() override;

   private:
    /**
     * @brief Initializes and configures a file sink for logging. Creates a text
     * output stream sink that writes log messages to the specified file.
     *
     * @throws std::runtime_error if the log file cannot be opened
     */
    void Init();

    /**
     * @brief Creates and initializes a file-based logging sink.
     *
     * This function:
     * 1. Creates a text output stream backend for Boost.Log;
     * 2. Initializes an ofstream to append to the specified log file;
     * 3. Verifies the file was successfully opened;
     * 4. Configures the sink to use the file stream with auto-flush enabled.
     *
     * @throws std::runtime_error if the log file cannot be opened
     */
    void CreateSink();

    /**
     * @brief Configures the log message format for the file-based logging sink.
     *
     * @example Format examples:
     * - Severity level is lower than `Debug`:
     * "2023-10-05 14:30:45 [INFO] Application started"
     * - Severity level is greater than and equal to `Debug`:
     * "2023-10-05 14:30:45 [DEBUG] [Thread: 0x7f8a] --> Application started"
     *
     * @note The conditional formatting ensures thread information is only
     * included in debug-level messages to avoid clutter in production logs.
     */
    void SetFormatter();

    /**
     * @brief Configures filtering rules for the file output sink.
     */
    void SetFilters();

   private:
    boost::shared_ptr<sink_t> sink_;
    FileSinkConfig config_;
};

}  // namespace sinks
}  // namespace logger
}  // namespace common