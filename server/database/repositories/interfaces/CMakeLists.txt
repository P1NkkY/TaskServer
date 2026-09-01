add_library(repo_interfaces INTERFACE include/itask_repository.h)

target_include_directories(
    repo_interfaces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(repo_interfaces INTERFACE Boost::headers)
