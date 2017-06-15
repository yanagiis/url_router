project(url_router)
cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/include)

option(ENABLE_TEST "build unit testing" ON)

if (${ENABLE_TEST})
    add_library(unity ${PROJECT_SOURCE_DIR}/3rdparty/Unity/src/unity.c)
    include_directories(${PROJECT_SOURCE_DIR}/3rdparty/Unity/src/)
    add_subdirectory(test)
endif ()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(bench)
add_subdirectory(example)

