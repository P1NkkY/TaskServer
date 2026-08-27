add_library(
    sink_logger
    include/logger_config.h
    include/sink_logger.h
    src/sink_logger.cpp
    src/sink_factory.h
    src/sink_factory.cpp
    src/sink_interface.h
    src/ofstream_sink.h
    src/ofstream_sink.cpp
    src/ostream_sink.h
    src/ostream_sink.cpp
    src/logger_config.cpp
)

target_include_directories(
    sink_logger
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(sink_logger PRIVATE Boost::log describe logger_interface)

# TODO Correct documentation after unit testing sink logger if necessary
