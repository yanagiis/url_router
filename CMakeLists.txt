project(url_router)
cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_path(DICT_INC NAMES dict/dict.h
	PATH ${CMAKE_PREFIX_PATH}/include)
find_library(DICT_LIB NAMES dict
	PATH ${CMAKE_PREFIX_PATH}/lib)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
