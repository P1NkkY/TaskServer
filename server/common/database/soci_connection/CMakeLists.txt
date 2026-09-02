find_package(SOCI REQUIRED)

add_library(
    soci_connection
    include/soci_connection.h
    include/soci_transaction.h
    src/soci_connection.cpp
    src/soci_transaction.cpp
)

target_include_directories(
    soci_connection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    soci_connection PRIVATE ${SOCI_LIBRARIES} database_common_interfaces
)
