add_library(
    database_common_interfaces
    INTERFACE
    include/iconnection.h
    include/itransaction.h
)

target_include_directories(
    database_common_interfaces INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
