add_library(logger_interface INTERFACE include/logger_interface.h)

target_include_directories(
    logger_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(logger_interface INTERFACE Boost::headers)
