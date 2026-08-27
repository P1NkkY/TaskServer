add_library(describe INTERFACE include/describe_enum.h)

target_include_directories(
    describe INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(describe INTERFACE Boost::headers)
