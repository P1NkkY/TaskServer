#pragma once

#include <string_view>

namespace common {
namespace logger {

enum class SeverityLevel { Trace, Debug, Info, Warning, Error, Critical, None };

class ILogger {
   public:
    virtual ~ILogger() = default;

    /**
     * @brief This function logs a message with the specified severity level
     *
     * @param level The severity level of the log message
     * @param message The actual log message text to be recorded
     */
    virtual void Log(SeverityLevel level, std::string_view message) = 0;
};

}  // namespace logger
}  // namespace common