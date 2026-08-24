#include <iostream>

#include "logger_config.h"
#include "sink_logger.h"

int main(int, char*[]) {
    common::logger::LoggerConfig* config = new common::logger::LoggerConfig();
    config->WithConsole(common::logger::Severity::Trace)
        .WithFile("test.log", common::logger::Severity::Trace);

    try {
        auto loggerPtr = new common::logger::SinkLogger(std::move(*config));
        {
            loggerPtr->Log(common::logger::Severity::Critical, "Hello");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
