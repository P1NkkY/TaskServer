#pragma once

#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace common {
namespace logger {
namespace sinks {

using sink_t = boost::log::sinks::synchronous_sink<
    boost::log::sinks::text_ostream_backend>;

class ISink {
   public:
    virtual ~ISink() {}

    virtual boost::shared_ptr<boost::log::sinks::sink> GetSink() = 0;
};

}  // namespace sinks
}  // namespace logger
}  // namespace common
