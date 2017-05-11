set(SRC bench.c)
add_executable(bench ${SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(bench url_router)
