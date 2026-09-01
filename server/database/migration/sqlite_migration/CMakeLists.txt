add_library(sqlite_migration include/migration.h src/migration.cpp)

target_include_directories(
    sqlite_migration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
