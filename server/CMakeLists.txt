add_executable(task_server main.cpp)

add_subdirectory(common)

target_link_libraries(
    task_server
    PRIVATE Boost::log
            describe
            logger_interface
            sink_logger
)
