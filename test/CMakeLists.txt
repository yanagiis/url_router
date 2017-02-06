set(SRC test_api.c
	test_url_tree.c)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test_api ${SRC})
target_link_libraries(test_api api_router unity)

add_executable(test_internal test_internal.c)
target_link_libraries(test_internal unity)
