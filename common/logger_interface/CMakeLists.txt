add_library(logger_interface include/logger_interface.h)

target_include_directories(
    logger_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
