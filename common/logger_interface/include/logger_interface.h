#pragma once

#include <boost/describe.hpp>
#include <string_view>

namespace common {
namespace logger {

/**
 * @brief Severity level.
 *
 */
enum class Severity {
    Trace,     ///< Trace messages
    Debug,     ///< Debug messages
    Info,      ///< Information messages
    Warning,   ///< Warnings
    Error,     ///< Errors that disrupt
    Critical,  ///< Critical failures that threaten system stability
    None       ///< No logging
};

BOOST_DESCRIBE_ENUM(Severity, Trace, Debug, Info, Warning, Error, Critical,
                    None)

class ILogger {
   public:
    virtual ~ILogger() = default;

    /**
     * @brief Checks whether a message with the specified logging level will
     * actually be logged.
     *
     * @param severity The requested logging level
     *
     * @return true if the specified logging level is active, false otherwise
     */
    virtual bool IsEnabled(Severity severity) = 0;

    /**
     * @brief This function logs a message with the specified severity level
     *
     * @param level The severity level of the log message
     * @param message The actual log message text to be recorded
     */
    virtual void Log(Severity level, std::string_view message) = 0;
};

}  // namespace logger
}  // namespace common