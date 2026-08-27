#pragma once

#include <boost/log/expressions/keyword.hpp>

#include "describe_enum.h"
#include "logger_interface.h"

namespace common {
namespace logger {

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", Severity)

inline std::ostream& operator<<(std::ostream& stream, Severity severity) {
    stream << common::describe::EnumToString(severity);

    return stream;
}

}  // namespace logger
}  // namespace common