#include "sink_logger.h"

#include <boost/log/core/core.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "attributes.h"
#include "logger_config.h"
#include "sink_factory.h"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace common {
namespace logger {

SinkLogger::SinkLogger(LoggerConfig&& config) {
    boost::shared_ptr<logging::core> core = logging::core::get();
    if (auto file_cfg = config.FileConfig()) {
        sinks::OfstreamFactory file_factory(file_cfg.value());
        auto ofstream_sink = file_factory.CreateSink();
        core->add_sink(ofstream_sink->GetSink());
    }
    if (auto console_cfg = config.ConsoleConfig()) {
        sinks::OstreamFactory clog_factory(console_cfg.value());
        auto ostream_sink = clog_factory.CreateSink();
        core->add_sink(ostream_sink->GetSink());
    }
    logging::add_common_attributes();
}

bool SinkLogger::IsEnabled(Severity level) {
    auto rec = logger_.open_record(keywords::severity = level);
    return static_cast<bool>(rec);
}

void SinkLogger::Log(Severity level, std::string_view message) {
    auto record = logger_.open_record(keywords::severity = level);

    if (record) {
        boost::log::record_ostream strm(record);
        strm << message;
        logger_.push_record(boost::move(record));
    }
}

}  // namespace logger
}  // namespace common
