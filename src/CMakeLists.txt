set(SRC args.c
	url_tree.c
	url_router.c)

add_library(url_router STATIC ${SRC})

install(TARGETS url_router
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
