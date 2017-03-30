set(SRC url_tree.c
	url_router.c)

add_library(url_router STATIC ${SRC})
target_include_directories(url_router PUBLIC ${DICT_INCLUDE_DIRS})
target_link_libraries(url_router ${DICT_LIBRARIES})

set_target_properties(url_router PROPERTIES
	COMPILE_FLAGS -Werror)

install(EXPORT url_router DESTINATION lib)
install(TARGETS url_router
	EXPORT url_router
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
