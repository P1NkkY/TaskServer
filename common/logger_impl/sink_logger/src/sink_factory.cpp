#include "sink_factory.h"

#include "ofstream_sink.h"
#include "ostream_sink.h"

namespace common {
namespace logger {
namespace sinks {

OstreamFactory::OstreamFactory(ConsoleSinkConfig config)
    : config_(std::move(config)) {}

ISink* OstreamFactory::CreateSink() {
    auto sink = new OstreamSink(config_);
    return sink;
}

OfstreamFactory::OfstreamFactory(FileSinkConfig config)
    : config_(std::move(config)) {}

ISink* OfstreamFactory::CreateSink() {
    auto sink = new OfstreamSink(config_);
    return sink;
}

}  // namespace sinks
}  // namespace logger
}  // namespace common