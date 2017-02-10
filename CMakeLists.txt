project(url_router)
cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_DIR}/include)
link_directories(${ROOT_DIR}/lib)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
