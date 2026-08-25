#include "sink_factory.h"

#include "ofstream_sink.h"
#include "ostream_sink.h"

namespace common {
namespace logger {
namespace sinks {

OstreamFactory::OstreamFactory(ConsoleSinkConfig config)
    : config_(std::move(config)) {}

std::shared_ptr<ISink> OstreamFactory::CreateSink() {
    auto sink = std::make_shared<OstreamSink>(config_);
    return sink;
}

OfstreamFactory::OfstreamFactory(FileSinkConfig config)
    : config_(std::move(config)) {}

std::shared_ptr<ISink> OfstreamFactory::CreateSink() {
    auto sink = std::make_shared<OfstreamSink>(config_);
    return sink;
}

}  // namespace sinks
}  // namespace logger
}  // namespace common