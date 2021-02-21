project(sync)

file(GLOB_RECURSE SYNC_SOURCE_LIST *.cpp)

add_executable(${PROJECT_NAME} ${SYNC_SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    boost_filesystem
    fmt
    pthread
)
