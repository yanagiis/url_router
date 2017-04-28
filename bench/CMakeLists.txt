set(SRC bench.c)
add_executable(bench ${SRC})
target_link_libraries(bench url_router)
