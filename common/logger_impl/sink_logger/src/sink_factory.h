#pragma once

#include "logger_config.h"
#include "sink_interface.h"

namespace common {
namespace logger {
namespace sinks {

class SinkFactory {
   public:
    virtual ~SinkFactory() {}

    virtual ISink* CreateSink() = 0;
};

class OstreamFactory : public SinkFactory {
   public:
    explicit OstreamFactory(ConsoleSinkConfig config);

    ISink* CreateSink() override;

   private:
    ConsoleSinkConfig config_;
};

class OfstreamFactory : public SinkFactory {
   public:
    explicit OfstreamFactory(FileSinkConfig config);

    ISink* CreateSink() override;

   private:
    FileSinkConfig config_;
};

}  // namespace sinks
}  // namespace logger
}  // namespace common
