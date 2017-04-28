project(url_router)
cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(dict MODULE REQUIRED)
find_package(unity MODULE REQUIRED)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)
add_subdirectory(example)
