add_library(
    logger_impl
    include/logger_config.h
    src/sink_interface.h
    src/logger_config.cpp
    src/ofstream_sink.h
    src/ostream_sink.h
    src/ofstream_sink.cpp
    src/ostream_sink.cpp
)

target_include_directories(
    logger_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    logger_impl PRIVATE Boost::headers describe logger_interface
)
