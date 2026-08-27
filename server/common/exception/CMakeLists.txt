add_library(exception INTERFACE include/exceptions.h)

target_include_directories(
    exception INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
