#pragma once

#include "logger_config.h"
#include "sink_interface.h"

namespace common {
namespace logger {
namespace sinks {

/**
 * @brief Console logging sink. This sink writes log records to std::clog using
 * Boost.Log text_ostream_backend. It is configured via ConsoleSinkConfig.
 *
 * @note The sink initializes itself in the constructor.
 */
class OstreamSink : public ISink {
   public:
    /**
     * @brief Constructs the console sink and immediately initializes it.
     *
     * @param config Configuration for the console sink
     *
     * @throws std::runtime_error If initialization fails.
     */
    explicit OstreamSink(ConsoleSinkConfig config);

    boost::shared_ptr<boost::log::sinks::sink> GetSink() override;

   private:
    /**
     * @brief Initializes the console output sink. Performs complete setup of
     * the console sink by:
     * 1. Creating the sink backend and frontend components
     * 2. Configuring formatting and filtering rules
     *
     */
    void Init();

    /**
     * @brief Creates and configures the console output sink components.
     *
     * This function:
     * 1. Creates a text output stream backend for Boost.Log
     * 2. Initializes the synchronous sink frontend with the backend
     * 3. Attaches std::clog as the output stream with a null deleter
     * 4. Configures the sink to use with auto-flush enabled.
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
    ConsoleSinkConfig config_;
};

}  // namespace sinks
}  // namespace logger
}  // namespace common