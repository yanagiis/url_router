include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test_url_router test_url_router.c)
target_link_libraries(test_url_router url_router unity)
set_target_properties(test_url_router PROPERTIES C_STANDARD 99)

add_executable(test_url_tree test_url_tree.c)
target_link_libraries(test_url_tree url_router unity)
set_target_properties(test_url_tree PROPERTIES C_STANDARD 99)
