#include "ofstream_sink.h"

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>

#include "attributes.h"
#include "logger_interface.h"

namespace expr = boost::log::expressions;

namespace common {
namespace logger {
namespace sinks {

OfstreamSink::OfstreamSink(LoggerConfig&& config) : config_(std::move(config)) {
    if (config_.FileConfig()->filename_.empty()) {
        throw std::runtime_error("OfstreamSink: filename is empty");
    }
    Init();
}

void OfstreamSink::Init() {
    CreateSink();
    SetFormatter();
    SetFilters();
}

boost::shared_ptr<boost::log::sinks::sink> OfstreamSink::GetSink() {
    return sink_;
}

void OfstreamSink::CreateSink() {
    boost::shared_ptr<boost::log::sinks::text_ostream_backend> backend =
        boost::make_shared<boost::log::sinks::text_ostream_backend>();
    sink_ = boost::make_shared<sink_t>(backend);

    boost::shared_ptr<std::ofstream> file_stream =
        boost::make_shared<std::ofstream>(config_.FileConfig()->filename_,
                                          std::ofstream::app);

    if (!file_stream->is_open()) {
        throw std::runtime_error("Can not open log file: " +
                                 config_.FileConfig()->filename_);
    }

    sink_->locked_backend()->add_stream(file_stream);
    sink_->locked_backend()->auto_flush(true);
}

void OfstreamSink::SetFormatter() {
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

void OfstreamSink::SetFilters() {
    sink_->set_filter(severity >= config_.FileConfig()->min_level_);
}

}  // namespace sinks
}  // namespace logger
}  // namespace common
