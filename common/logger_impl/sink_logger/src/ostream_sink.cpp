#include "ostream_sink.h"

#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread/thread.hpp>

#include "attributes.h"
#include "logger_interface.h"

namespace expr = boost::log::expressions;

namespace common {
namespace logger {
namespace sinks {

OstreamSink::OstreamSink(ConsoleSinkConfig config)
    : config_(std::move(config)) {
    Init();
}

void OstreamSink::Init() {
    CreateSink();
    SetFormatter();
    SetFilters();
}

boost::shared_ptr<boost::log::sinks::sink> OstreamSink::GetSink() {
    return sink_;
}

void OstreamSink::CreateSink() {
    boost::shared_ptr<boost::log::sinks::text_ostream_backend> backend =
        boost::make_shared<boost::log::sinks::text_ostream_backend>();
    sink_ = boost::make_shared<sink_t>(backend);

    sink_->locked_backend()->add_stream(
        boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    sink_->locked_backend()->auto_flush(true);
}

void OstreamSink::SetFormatter() {
    boost::log::formatter fmt =
        expr::stream
        << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
                                                            "%Y-%m-%d %H:%M:%S")
        << " [" << severity << "] "
        << expr::if_(severity <= common::logger::Severity::Debug)
               [expr::stream << "[Thread: " << boost::this_thread::get_id()
                             << "] ---> "]
        << expr::smessage;

    sink_->set_formatter(fmt);
}

void OstreamSink::SetFilters() {
    sink_->set_filter(severity >= config_.min_level_);
}

}  // namespace sinks
}  // namespace logger
}  // namespace common
