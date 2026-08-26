add_executable(logger_example logger_ex.cpp)

target_link_libraries(
    logger_example
    PUBLIC Boost::log
           describe
           logger_interface
           sink_logger
)
