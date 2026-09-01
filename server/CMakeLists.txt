add_executable(task_server main.cpp)

add_subdirectory(common)
add_subdirectory(database)

target_link_libraries(
    task_server
    PRIVATE Boost::log
            describe
            exception
            logger_interface
            sink_logger
)
